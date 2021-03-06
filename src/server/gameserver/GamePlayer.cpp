//////////////////////////////////////////////////////////////////////////////
// Filename    : GamePlyaer.cpp 
// Written By  : reiot@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "GamePlayer.h"
#include "Assert.h"
#include "Creature.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "LogClient.h"
#include "Zone.h"
#include "RelicUtil.h"
#include "PacketFactoryManager.h"
#include "PacketValidator.h"
#include "IncomingPlayerManager.h"
#include "PCFinder.h"
#include "TelephoneCenter.h"
#include "DB.h"
#include "VSDateTime.h"
#include "Thread.h"
#include "GuildManager.h"
#include "Guild.h"
#include "VariableManager.h"
#include "SharedServerManager.h"
#include "BillingInfo.h"
#include "BillingPlayerManager.h"
#include <fstream>
#include "Properties.h"
#include "EventKick.h"
#include "StringPool.h"

#include "CGConnect.h"
#include "GSGuildMemberLogOn.h"
#include "GCKickMessage.h"
#include "GCSystemMessage.h"

#include "ServiceDeadline.h"

#include "chinabilling/CBillingInfo.h"
#ifdef __CONNECT_CBILLING_SYSTEM__
	#include "chinabilling/CBillingPlayerManager.h"
#endif

#include <stdio.h>


//////////////////////////////////////////////////////////////////////////////
// 葛电 packet甸俊 措秦辑 profiling茄促. by sigi. 2002.5.6
//
// 窜, 捞吧 荤侩窍扁 困秦辑绰 
// Profile.h俊 MAX_PROFILE_SAMPLES += 300阑 秦拎具 茄促.
//////////////////////////////////////////////////////////////////////////////
//#define __PROFILE_PACKETS__

#ifdef __PROFILE_PACKETS__
	#include "Profile.h"
#endif

// by sigi. 2002.11.12
const int defaultGamePlayerInputStreamSize = 1024;
const int defaultGamePlayerOutputStreamSize = 20480;

static int maxIdleSec         = 60* 5;		// 无动作时间最大保持连接时间 60 * 5 = 300秒(5分)
//static int maxSpeedVerifyTime = 2;  		// 0.3 檬
static int maxVerifyCount     = 3;      	// 最大错误校验次数 3次
static int maxTimeGap         =	5;			// 时间校验偏差秒数 韩服为5次 修改为8次
static int SpeedCheckDelay    = 60;			// 时间校验间隔60秒一次

const int PCRoomLottoSec = 3600;			// 3600 檬. 1矫埃
const int PCRoomLottoMaxAmount = 3;			// 茄锅俊 阶老 荐 乐绰 弥措 汗鼻荐
// CLLoginHandler.cpp俊 乐绰 窃荐促.
void addLogoutPlayerData(Player* pPlayer);


//////////////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////////////

GamePlayer::GamePlayer (Socket* pSocket)
: //Player(pSocket), 	// by sigi. 2002.11.12
	m_pCreature(NULL), m_PlayerStatus(GPS_NONE), m_pReconnectPacket(NULL),m_Sequence(0)
{
	__BEGIN_TRY

	Assert( pSocket != NULL );
	m_pSocket = pSocket;

#ifdef __USE_ENCRYPTER__
	// create socket input stream
	m_pInputStream = new SocketEncryptInputStream( m_pSocket, defaultGamePlayerInputStreamSize );
	Assert( m_pInputStream != NULL );
	
	// create socket output stream
	m_pOutputStream = new SocketEncryptOutputStream( m_pSocket, defaultGamePlayerOutputStreamSize );
	Assert( m_pOutputStream != NULL );
#else
	// create socket input stream
	m_pInputStream = new SockettInputStream( m_pSocket, defaultGamePlayerInputStreamSize );
	Assert( m_pInputStream != NULL );
	
	// create socket output stream
	m_pOutputStream = new SockettOutputStream( m_pSocket, defaultGamePlayerOutputStreamSize );
	Assert( m_pOutputStream != NULL );
#endif

	m_Mutex.setName("GamePlayer");
		
	getCurrentTime(m_ExpireTime);
	m_ExpireTime.tv_sec += maxIdleSec;

    // 泅犁 矫埃阑 罐酒柯促
	//getCurrentTime(m_SpeedVerify);
	m_SpeedVerify.tv_sec = 0;;
	m_SpeedVerify.tv_usec = 0;;
	getCurrentTime(m_MoveSpeedVerify);
	getCurrentTime(m_AttackSpeedVerify);

	m_VerifyCount = 0;
	
	m_SpecialEventCount = 0;

	m_bKickForLogin = false;
	
	m_bFreePass = false;

	m_bMetroFreePlayer = false;

//	if ( m_bPCRoomPlay )
//		m_ItemRatioBonusPoint = g_pVariableManager->getPCRoomItemRatioBonusPercent();
//	else
		m_ItemRatioBonusPoint = 0;

	m_PCRoomLottoStartTime.tv_sec = 0;
	m_PCRoomLottoStartTime.tv_usec = 0;
	m_PCRoomLottoSumTime = 0;

	m_bPacketLog = false;

	// 按眉啊 积己等 矫痢阑 肺弊牢茄 矫埃栏肺 夯促.
	m_LoginDateTime = VSDateTime::currentDateTime();

#ifdef	__THAILAND_SERVER__
	m_bPermission = false;
#endif
	
  //	m_NProtectCSAuth.Init();

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////////////

GamePlayer::~GamePlayer ()
{
	__BEGIN_TRY

	//__ENTER_CRITICAL_SECTION(m_Mutex)

	// 弊 绢恫 敲饭捞绢 按眉啊 昏力瞪 锭俊档, 弊 惑怕绰 肺弊酒眶捞绢具 茄促.
	// 溜 绢恫 敲饭捞绢甫 立加 辆丰 矫虐妨搁, 弊 惑怕甫 肺弊酒眶栏肺 父甸绢具 茄促.
	Assert(m_PlayerStatus == GPS_END_SESSION);

	try
	{
		// Delete creature
		if (m_pCreature != NULL) 
		{
			// 己辑 冻绢哆府扁
			if ( m_pCreature->hasRelicItem() )
			{
				dropRelicToZone( m_pCreature, false );
			}

			dropFlagToZone( m_pCreature, false );
			dropSweeperToZone( m_pCreature );

			//try 
			//{
				// NoSuch力芭. by sigi. 2002.5.2
				g_pPCFinder->deleteCreature(m_pCreature->getName());
			//} 
			//catch (NoSuchElementException & t) 
			//{
			//}

		#ifdef __CONNECT_BILLING_SYSTEM__
			// Pay 辆丰茄促绊 舅妨霖促. by sigi. 2002.11.18
			if ( isBillingPlayAvaiable() && !m_bMetroFreePlayer )	// by sigi. 2002.11.23
			{
				g_pBillingPlayerManager->sendPayLogout( this );
			}
		#elif defined(__CONNECT_CBILLING_SYSTEM__ )
			// 吝惫 呼傅 辑滚俊 logout 菩哦阑 焊辰促.
			g_pCBillingPlayerManager->sendLogout( this );
		#endif

			Statement* pStmt = NULL;

			// 辨靛 泅犁 立加 糕滚 府胶飘俊辑 昏力茄促.
			if ( m_pCreature->isSlayer() )
			{
				Slayer* pSlayer = dynamic_cast<Slayer*>(m_pCreature);
				if ( pSlayer->getGuildID() != 99 )
				{
					Guild* pGuild = g_pGuildManager->getGuild( pSlayer->getGuildID() );
					if ( pGuild != NULL )
					{
						pGuild->deleteCurrentMember( pSlayer->getName() );

						GSGuildMemberLogOn gsGuildMemberLogOn;
						gsGuildMemberLogOn.setGuildID( pGuild->getID() );
						gsGuildMemberLogOn.setName( pSlayer->getName() );
						gsGuildMemberLogOn.setLogOn( false );

						g_pSharedServerManager->sendPacket( &gsGuildMemberLogOn );
						
						// 叼厚俊 诀单捞飘 茄促.
						BEGIN_DB
						{
							pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
							pStmt->executeQuery( "UPDATE GuildMember SET LogOn = 0 WHERE Name = '%s'", pSlayer->getName().c_str() );
						}
						END_DB(pStmt)
					}
					else
						filelog( "GuildMissing.log", "[NoSuchGuild] GuildID : %d, Name : %s\n", (int)pSlayer->getGuildID(), pSlayer->getName().c_str() );
				}
			}
			else if ( m_pCreature->isVampire() )
			{
				Vampire* pVampire = dynamic_cast<Vampire*>(m_pCreature);
				if ( pVampire->getGuildID() != 0 )
				{
					Guild* pGuild = g_pGuildManager->getGuild( pVampire->getGuildID() );
					if ( pGuild != NULL )
					{
						pGuild->deleteCurrentMember( pVampire->getName() );

						GSGuildMemberLogOn gsGuildMemberLogOn;
						gsGuildMemberLogOn.setGuildID( pGuild->getID() );
						gsGuildMemberLogOn.setName( pVampire->getName() );
						gsGuildMemberLogOn.setLogOn( false );

						g_pSharedServerManager->sendPacket( &gsGuildMemberLogOn );

						// 叼厚俊 诀单捞飘 茄促.
						BEGIN_DB
						{
							pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
							pStmt->executeQuery( "UPDATE GuildMember SET LogOn = 0 WHERE Name = '%s'", pVampire->getName().c_str() );
						}
						END_DB(pStmt)
					}
					else
						filelog( "GuildMissing.log", "[NoSuchGuild] GuildID : %d, Name : %s\n", (int)pVampire->getGuildID(), pVampire->getName().c_str() );
				}
			}
			else if ( m_pCreature->isOusters() )
			{
				Ousters* pOusters = dynamic_cast<Ousters*>(m_pCreature);
				if ( pOusters->getGuildID() != 66 )
				{
					Guild* pGuild = g_pGuildManager->getGuild( pOusters->getGuildID() );
					if ( pGuild != NULL )
					{
						pGuild->deleteCurrentMember( pOusters->getName() );

						GSGuildMemberLogOn gsGuildMemberLogOn;
						gsGuildMemberLogOn.setGuildID( pGuild->getID() );
						gsGuildMemberLogOn.setName( pOusters->getName() );
						gsGuildMemberLogOn.setLogOn( false );

						g_pSharedServerManager->sendPacket( &gsGuildMemberLogOn );

						// 叼厚俊 诀单捞飘 茄促.
						BEGIN_DB
						{
							pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
							pStmt->executeQuery( "UPDATE GuildMember SET LogOn = 0 WHERE Name = '%s'", pOusters->getName().c_str() );
						}
						END_DB(pStmt)
					}
					else
						filelog( "GuildMissing.log", "[NoSuchGuild] GuildID : %d, Name : %s\n", (int)pOusters->getGuildID(), pOusters->getName().c_str() );
				}
			}

			int PartyID = m_pCreature->getPartyID();

			if (PartyID != 0)
			{
				Zone* pZone = m_pCreature->getZone();
				if (pZone != NULL)
				{
					LocalPartyManager* pLocalPartyManager = pZone->getLocalPartyManager();
					pLocalPartyManager->deletePartyMember(PartyID, m_pCreature);
				}
			}

			SAFE_DELETE(m_pCreature);
			//m_pCreature->setPlayer( NULL );
		}
	}
	catch (NoSuchElementException& nsee)
	{
		cerr << "GamePlayer::~GamePlayer() : " << nsee.toString() << endl;
		throw ("GamePlayer::~GamePlayer() : NoSuchElementException");
	}
	catch (Throwable& t )
	{
		t.addStack( __PRETTY_FUNCTION__ );
		throw;
	}

	// 菩哦阑 昏力茄促.
	while (!m_PacketHistory.empty()) 
	{
		Packet* pPacket = m_PacketHistory.front();
		SAFE_DELETE(pPacket);
		m_PacketHistory.pop_front();
	}

	SAFE_DELETE(m_pReconnectPacket);

	//__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}
//////////////////////////////////////////////////////////////////////////
//
// 两个timeval结构相减
//
//////////////////////////////////////////////////////////////////////////
void GamePlayer::tv_sub(struct timeval *out,struct timeval *in) 
{ 
	if( (out->tv_usec-=in->tv_usec)<0) 
	{ 
		--out->tv_sec; 
		out->tv_usec +=1000000; 
	} 
	out->tv_sec-=in->tv_sec; 
} 
/*------------- The End -----------*/
//////////////////////////////////////////////////////////////////////
//
// parse packet and execute handler for the packet
//
//////////////////////////////////////////////////////////////////////
void GamePlayer::processCommand (bool Option) 
{
	__BEGIN_TRY

	// 庆歹甫 烙矫历厘且 滚欺 积己
	char header[szPacketHeader];
	PacketID_t packetID;
	PacketSize_t packetSize;
	// add by Coffee 增加封包序列
	SequenceSize_t packetSequence;

	Packet* pPacket = NULL;

	try {

		// 菩澄萍甫 罐绊 乐绰 荤侩磊 老 版快 捞 何盒俊辑 贸府 秦霖促.
		// 菩澄萍甫 罐绰 版快 绢恫 抗寇 惑炔捞 惯积且瘤 葛福骨肺,
		// 决断是否需要断开当前ID连接
		if (isPenaltyFlag(PENALTY_TYPE_KICKED))
		{
			filelog("GamePlayer.txt", "Penalty Kicked. Name[%s],Host[%s],Type[%d]", 
												((getCreature()==NULL)?"NULL":getCreature()->getName().c_str()), 
												((getSocket()==NULL)?"NULL":getSocket()->getHost().c_str()),
												m_ItemRatioBonusPoint);

			throw DisconnectException("He is had penalty");
		}

		if (Option) 
		{
			m_EventManager.heartbeat();
		}

		// 涝仿滚欺俊 甸绢乐绰 肯傈茄 菩哦甸阑 葛炼府 贸府茄促.
		while (true) 
		{
			// 涝仿胶飘覆俊辑 菩哦庆歹农扁父怒 佬绢夯促.
			// 父距 瘤沥茄 农扁父怒 胶飘覆俊辑 佬阑 荐 绝促搁,
			// Insufficient 抗寇啊 惯积窍绊, 风橇甫 狐廉唱埃促.
			// NoSuch力芭. by sigi. 2002.5.4
			if (!m_pInputStream->peek(&header[0] , szPacketHeader))
			{
				Timeval currentTime;
				getCurrentTime(currentTime);
				if (currentTime >= m_ExpireTime)
				{
					filelog("GamePlayer.txt", "Timeout Disconnect1. Name[%s],Host[%s]", 
												((getCreature()==NULL)?"NULL":getCreature()->getName().c_str()), 
												((getSocket()==NULL)?"NULL":getSocket()->getHost().c_str()));

					throw DisconnectException("老沥 矫埃悼救 涝仿窍瘤 臼阑 版快, 楷搬阑 辆丰钦聪促.");
				}

				break;
			}
			
			// 菩哦酒捞叼 棺 菩哦农扁甫 舅酒辰促.
			// 捞锭 菩哦农扁绰 庆歹甫 器窃茄促.
			memcpy(&packetID   , &header[0] , szPacketID);	
			memcpy(&packetSize , &header[szPacketID] , szPacketSize);
			// 读取封包序列

			memcpy( &packetSequence , &header[szPacketID+szPacketSize] , szSequenceSize );
			// 判断封包序列是否合法
			if ( packetSequence!= m_Sequence)
			{
				filelog("SequenceError.txt", "Timeout Disconnect1. Name[%s],Host[%s]", 
					((getCreature()==NULL)?"NULL":getCreature()->getName().c_str()), 
					((getSocket()==NULL)?"NULL":getSocket()->getHost().c_str()));
				throw DisconnectException("封包序列错误");
			}
			m_Sequence++;

			// 判断封包ID是否合法
			if (packetID >= (int)Packet::PACKET_MAX)
			{
				filelog("GamePlayer.txt", "Packet ID exceed MAX, RECV [%d/%d],ID[%s],Host[%s]", 
					packetID, 
					Packet::PACKET_MAX,
					m_ID.c_str(),
//					getCreature()->getName().c_str(), 
					getSocket()->getHost().c_str());

				throw InvalidProtocolException("too large packet id");
			}

			try 
			{
				// 菩哦 鉴辑啊 棵官弗瘤 八刘茄促.
				if (! g_pPacketValidator->isValidPacketID(getPlayerStatus() , packetID))
				{
					filelog("GamePlayer.txt", "Not Valid Packet, RECV [%d],ID[%s],Host[%s]", 
						packetID, 
						m_ID.c_str(),
//						getCreature()->getName().c_str(), 
						getSocket()->getHost().c_str());
					throw InvalidProtocolException("invalid packet order");
				}

//跳过导致当机的非法报文
				if (packetID==Packet::PACKET_GC_OTHER_STORE_INFO || packetID==Packet::PACKET_GC_MY_STORE_INFO)
				{
					filelog("GamePlayer.txt", "Not Valid Packet, RECV [%d],ID[%s],Host[%s]", 
						packetID, 
						m_ID.c_str(),
//						getCreature()->getName().c_str(), 
						getSocket()->getHost().c_str());
					throw InvalidProtocolException("invalid packet order");
				}
			
				// 菩哦 农扁啊 呈公 农搁 橇肺配妮 俊矾肺 埃林茄促.
				if (packetSize > g_pPacketFactoryManager->getPacketMaxSize(packetID))
				{
					filelog("GamePlayer.txt", "Too Larget Packet Size, RECV [%d],PacketSize[%d/%d],ID[%s],Host[%s]", 
						packetID, packetSize, g_pPacketFactoryManager->getPacketMaxSize(packetID),
						m_ID.c_str(),
//						getCreature()->getName().c_str(), 
						getSocket()->getHost().c_str());
					throw InvalidProtocolException("too large packet size");
				}
			
				// 判断封包数据是否接收完毕
				if (m_pInputStream->length() < szPacketHeader + packetSize)
					//throw InsufficientDataException();
					break;

				// 当前时间
				getCurrentTime(m_ExpireTime);
				m_ExpireTime.tv_sec += maxIdleSec;
			
				// 咯扁鳖瘤 吭促搁 涝仿滚欺俊绰 肯傈茄 菩哦 窍唱 捞惑捞 甸绢乐促绰 舵捞促.
				// 菩哦蒲配府概聪历肺何磐 菩哦酒捞叼甫 荤侩秦辑 菩哦 胶飘钒贸甫 积己窍搁 等促.
				// 菩哦酒捞叼啊 肋给瞪 版快绰 菩哦蒲配府概聪历俊辑 贸府茄促.
				pPacket = g_pPacketFactoryManager->createPacket(packetID);

				// 捞力 捞 菩哦胶飘钒贸甫 檬扁拳茄促.
				// 菩哦窍困努贰胶俊 沥狼等 read()啊 virtual 皋目聪硫俊 狼秦辑 龋免登绢
				// 磊悼利栏肺 檬扁拳等促.
				m_pInputStream->readPacket(pPacket);

				// 泅犁 菩哦阑 菩哦 洒胶配府狼 盖 第俊 持绰促.
				m_PacketHistory.push_back(pPacket);

				// packet file log甫 巢变促.
				if ( m_bPacketLog )
				{
					Timeval currentTime;
					getCurrentTime( currentTime );

					if ( currentTime >= m_PacketLogEndTime )
					{
						m_bPacketLog = false;
					}
					else
					{
						filelog( m_PacketLogFileName.c_str(), "%s", pPacket->toString().c_str() );
					}
				}

				//cout << "[" << (int)Thread::self() << "] execute before : " << pPacket->getPacketName().c_str() << endl;
	
				// 捞力 捞 菩哦胶飘钒贸甫 啊瘤绊 菩哦勤甸矾甫 荐青窍搁 等促.
				// 菩哦酒捞叼啊 肋给瞪 版快绰 菩哦勤甸矾概聪历俊辑 贸府茄促.
				try
				{
				#ifdef __PROFILE_PACKETS__
					
					beginProfileEx(	pPacket->getPacketName().c_str() );
					pPacket->execute(this);
					endProfileEx( pPacket->getPacketName().c_str() );

				#else
					verifySpeed(pPacket);
					pPacket->execute(this);
				#endif
				}  /*catch ( Throwable& t )
				{
					filelog( "GPPC.txt", "%s PacketID : %d", t.toString().c_str(), packetID );
					throw DisconnectException("GamePlayer Error 1!");
				}*/catch(...)
					{
						filelog("GamePlayerError.txt","Player:[%s], IP:[%s],MAC:[%02x%02x%02x%02x%02x%02x],Packet is:%s",m_ID.c_str(),getSocket()->getHost().c_str(),
							m_MacAddress[0],m_MacAddress[1],m_MacAddress[2],m_MacAddress[3],m_MacAddress[4],m_MacAddress[5],
							pPacket->toString().c_str());
						throw DisconnectException("GamePlayer Error 2!");
					}
				//cout << "[" << (int)Thread::self() << "] execute after : " << pPacket->getPacketName().c_str() << endl;

				// 菩哦阑 nPacketHistorySize 俺父怒父 历厘茄促.
				while (m_PacketHistory.size() > nPacketHistorySize) 
				{
					Packet* oldPacket = m_PacketHistory.front();
					SAFE_DELETE(oldPacket);
					m_PacketHistory.pop_front();
				}
			} 
			catch (IgnorePacketException & igpe) 
			{
				// PacketValidator 俊辑 菩哦阑 公矫窍扼绊 沁栏聪,
				// 涝仿胶飘覆俊辑 葛滴 瘤况滚府绊 角青窍瘤 臼档废 茄促.

				// 菩哦 农扁啊 呈公 农搁 橇肺配妮 俊矾肺 埃林茄促.
				if (packetSize > g_pPacketFactoryManager->getPacketMaxSize(packetID))
				{
					filelog("GamePlayer.txt", "Too Larget Packet Size[Ignore], RECV [%d],PacketSize[%d],Name[%s],Host[%s]", 
																packetID, packetSize,
																((getCreature()==NULL)?"NULL":getCreature()->getName().c_str()), 
																((getSocket()==NULL)?"NULL":getSocket()->getHost().c_str()));
					throw InvalidProtocolException("too large packet sizeIgnore");
				}
			
				// 涝仿滚欺郴俊 菩哦农扁父怒狼 单捞鸥啊 甸绢乐绰瘤 犬牢茄促.
				// 弥利拳矫 break 甫 荤侩窍搁 等促. (咯扁辑绰 老窜 exception阑 镜 巴捞促.)
				if (m_pInputStream->length() < szPacketHeader + packetSize)
					throw InsufficientDataException();

				// 单捞鸥啊 葛滴 档馒沁栏搁, 弊 农扁父怒 公矫窍绊,
				// 促弗 菩哦阑 贸府窍档废 茄促....
				m_pInputStream->skip(szPacketHeader + packetSize);

				// 公矫等 菩哦篮, expire 俊 康氢阑 林瘤 臼霸 等促.
				// 溜 蜡瓤茄 菩哦父捞 漏府瘤 臼霸 秦霖促.
				// 肚茄 洒胶配府俊档 甸绢啊瘤 臼绰促.
			}
		}
	} 
	catch (InsufficientDataException & ide) 
	{
		// expire time 阑 檬苞沁阑 版快 楷搬阑 辆丰茄促.
		Timeval currentTime;
		getCurrentTime(currentTime);
		if (currentTime >= m_ExpireTime)
		{
			filelog("GamePlayer.txt", "Timeout Diconnect. Name[%s],Host[%s]", 
												((getCreature()==NULL)?"NULL":getCreature()->getName().c_str()), 
												((getSocket()==NULL)?"NULL":getSocket()->getHost().c_str()));

			throw DisconnectException("老沥 矫埃悼救 涝仿窍瘤 臼阑 版快, 楷搬阑 辆丰钦聪促.");
		}
	}
	// 林籍贸府 by sigi. 2002.5.14
	/*
	catch (InvalidProtocolException & ipe) 
	{
		// 立加阑 碍力辆丰矫难具 茄促. 公郊 规过栏肺??
		throw;
	} 
	catch (Throwable & t) 
	{
		//cerr << t.toString() << endl;
		//cerr << "GamePlayer Throwable Exception Check!" << endl;
		throw;
	}
	*/

	__END_CATCH
}
		    

//////////////////////////////////////////////////////////////////////
//
// flush output buffer to socket's send buffer
//
// flush且 悼救 促弗 静饭靛俊辑 免仿 滚欺俊 sendPacket阑 龋免秦辑绰 救等促.
// (捞凡 版快绰 辑滚埃 烹脚栏肺 say啊 朝酒坷绰 巴观俊 绝促.)
//
//////////////////////////////////////////////////////////////////////
void GamePlayer::processOutput () 
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	int i = 0;
		
	try 
	{
		Player::processOutput();

		i = 100000;
	} 
	catch (InvalidProtocolException & It) 
	{
		//cerr << "GamePlayer::processOutput Exception Check!!" << endl;
		//cerr << It.toString() << endl;
		//cerr << "劳剂记 车绰单...... 酒捞绰 割牢绊?" << (int)i << endl;
		throw DisconnectException("Pipe 楷搬狼 颇鲍肺 立加阑 楼弗促");
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// send packet to player's output buffer
//
//////////////////////////////////////////////////////////////////////
void GamePlayer::sendPacket (Packet* pPacket) 
{	
	__BEGIN_TRY
	
	__ENTER_CRITICAL_SECTION(m_Mutex)

	try 
	{
		// packet file log甫 巢变促.
		if ( m_bPacketLog )
		{
			Timeval currentTime;
			getCurrentTime( currentTime );

			if ( currentTime >= m_PacketLogEndTime )
			{
				m_bPacketLog = false;
			}
			else
			{
				filelog( m_PacketLogFileName.c_str(), "%s", pPacket->toString().c_str() );
			}
		}

		Player::sendPacket(pPacket);

		//cout << "GamePlayer::sendPacket() : " << pPacket->toString() << endl;
		//cout << "GamePlayer::sendPacket() PACKET SIZE : " << pPacket->getPacketSize() << endl;

		/*
		if (getCreature() != NULL)
		{
			PacketID_t packetID = pPacket->getPacketID();
			switch (packetID)
			{
				case Packet::PACKET_GC_UPDATE_INFO:
				case Packet::PACKET_GC_MOVE_OK:
				case Packet::PACKET_GC_SET_POSITION:
					filelog("GamePlayer.txt", "SEND [%s],Name[%s],Host[%s]", 
							pPacket->getPacketName().c_str(), 
							getCreature()->getName().c_str(), 
							getSocket()->getHost().c_str());
					break;
				default:
					break;
			}
		}
		else
		{
			PacketID_t packetID = pPacket->getPacketID();
			switch (packetID)
			{
				case Packet::PACKET_GC_UPDATE_INFO:
				case Packet::PACKET_GC_MOVE_OK:
				case Packet::PACKET_GC_SET_POSITION:
					filelog("GamePlayer.txt", "SEND [%s],Name[NULL],Host[%s]", 
							pPacket->getPacketName().c_str(), 
							getSocket()->getHost().c_str());
					break;
				default:
					break;
			}
		}
		*/
	} 
	catch (InvalidProtocolException & It) 
	{
		//cout << "GamePlayer::sendPacket Exception Check!!" << endl;
		//cout << It.toString() << endl;
		//throw DisconnectException("Pipe 楷搬狼 颇鲍肺 立加阑 楼弗促");
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}


//--------------------------------------------------------------------------------
//
// disconnect player
//
// (1) 农府贸啊 粮犁且 版快, 粮俊辑 昏力窍绊 宏肺靛某胶飘茄促.
// (2) 农府贸甫 历厘茄促.
//
//--------------------------------------------------------------------------------
void GamePlayer::disconnect (bool bDisconnected)
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	//--------------------------------------------------------------------------------
	// 农府贸甫 粮俊辑 昏力茄 饶, 林函狼 PC甸俊霸 宏肺靛某胶飘秦霖促.
	// 弊促澜 农府贸甫 DB俊 历厘茄促.
	//--------------------------------------------------------------------------------
	string CreatureName = "";
	if (m_pCreature != NULL) 
	{
		CreatureName = m_pCreature->getName();

		try 
		{
			// GPS_NORMAL 牢 版快俊父, 粮俊 农府贸啊 甸绢啊 乐霸 等促.
			// *CAUTION*
			// 趣矫 pushPC()啊 龋免等 饶俊 楷搬捞 辆丰登搁 绢痘霸 窍唱.. 扼绊 捌沥且 啊瓷己档 乐促.
			// 弊矾唱, 贸府 风凭狼 鉴辑甫 肋 混旗焊搁 弊繁 捌沥阑 且 鞘夸啊 绝促.
			// 绢瞒乔 楷搬捞 谗扁歹扼档, 粮捞 贸府等 饶 农府贸啊 角力 鸥老肺 棵扼埃 促澜,
			// 促矫 敲饭捞绢狼 贸府风橇啊 倒酒坷扁 锭巩捞促.
			if (getPlayerStatus() == GPS_NORMAL) 
			{
				//----------------------------------
				// 粮俊辑 昏力窍绊 宏肺靛某胶飘茄促.
				//----------------------------------
				Zone* pZone = m_pCreature->getZone();
				Assert(pZone != NULL);
				pZone->deleteQueuePC(m_pCreature);
				pZone->deleteCreature(m_pCreature , m_pCreature->getX() , m_pCreature->getY());
				//--------------------------------------------------------------------------------
				// 农府贸甫 历厘茄促.
				//--------------------------------------------------------------------------------
				m_pCreature->save();
			} 
		} 
		catch (Throwable & t) 
		{
		}
	}

	setPlayerStatus(GPS_END_SESSION);

	//--------------------------------------------------------------------------------
    // 酒捞叼啊 汲沥登菌促绰 舵篮, 肺弊牢捞 捞风绢脸促绰 舵捞促.
	//--------------------------------------------------------------------------------
    if (m_ID != "")
    {
        Statement* pStmt1 = NULL;
        Statement* pStmt2 = NULL;

		BEGIN_DB
		{

//            pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
            // 肺弊坷橇肺 函版茄促.
	      	//pStmt1 = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
			pStmt1 = g_pDatabaseManager->getDistConnection( "PLAYER_DB" )->createStatement();

			// LogOn捞 GAME惑怕牢 版快父 LOGOFF肺 官槽促. by sigi. 2002.5.15
            pStmt1->executeQuery("UPDATE Player SET LogOn='LOGOFF', LastLogoutDate=now() WHERE PlayerID = '%s' AND LogOn='GAME'" , m_ID.c_str());

			// LogoutPlayerData 俊 眠啊茄促.
		//	addLogoutPlayerData(this);

			if (pStmt1->getAffectedRowCount()==0)
			{
				// 捞固 LOGOFF芭唱
				// LOGON惑怕牢啊?
				// 捞凡 荐 乐阑鳖? -_-;
			}

			// 呼傅 by sigi. 2002.5.31
#if defined(__PAY_SYSTEM_LOGIN__) || defined(__PAY_SYSTEM_ZONE__) || defined(__PAY_SYSTEM_FREE_LIMIT__)
			if (isPayPlaying() || isPremiumPlay())
			{
				logoutPayPlay( m_ID );
			}
#endif


			SAFE_DELETE(pStmt1);

		}
		END_DB(pStmt1)
		BEGIN_DB
        {

			// IP 沥焊甫 昏力秦 霖促.
            pStmt2 = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
            pStmt2->executeQuery("DELETE FROM UserIPInfo WHERE Name = '%s'", CreatureName.c_str());

			SAFE_DELETE(pStmt2);
        }
		END_DB(pStmt2)
    }

	// login辑滚肺 啊扼绊 client俊霸 焊辰促.
	// 盔贰绰 LGIncomingConnectionOKHandler俊辑 贸府沁促. by sigi. 2002.6.19
	if (m_pReconnectPacket!=NULL)
	{
		//cout << "[SendReconnect] " << m_pReconnectPacket->toString().c_str() << endl;

		try 
		{
			//sendPacket( m_pReconnectPacket );
			Player::sendPacket( m_pReconnectPacket );
			// 免仿 滚欺俊 巢酒乐绰 单捞鸥甫 傈价茄促.
			m_pOutputStream->flush();
		} 
		catch (Throwable & t) 
		{
			// 公矫
		}
		
		SAFE_DELETE(m_pReconnectPacket);
	}


	// 窃荐 拉何盒俊辑 贸府沁绰单.. 鸥捞怪 巩力(LogOn捞唱 UserIPInfo 殿)肺
	// 咯扁辑 谗绢林绊.. 犁立菩哦~阑 焊郴档废 茄促.
	if (bDisconnected == UNDISCONNECTED) 
	{
		try 
		{
			// 努扼捞攫飘俊霸 GCDisconnect 菩哦阑 傈价茄促.
			//GCDisconnect gcDisconnect;
			//sendPacket(gcDisconnect);

			// 免仿 滚欺俊 巢酒乐绰 单捞鸥甫 傈价茄促.
			m_pOutputStream->flush();
		} 
		catch (Throwable & t) 
		{
			//cerr << "GamePlayer::disconnect() : GamePlayer::disconnect Exception Check!!" << endl;
			//cerr << t.toString() << endl;
		}
	}

	// 家南 楷搬阑 摧绰促.
	m_pSocket->close();

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// 弥辟 N 锅掳狼 菩哦阑 府畔茄促.
// 
// N == 0 老 版快, 啊厘 弥辟狼 菩哦阑 府畔窍霸 等促.
//
// 弥措 nPacketHistorySize - 1 鳖瘤 瘤沥且 荐 乐促. 
//
//////////////////////////////////////////////////////////////////////
Packet* GamePlayer::getOldPacket (uint prev)
{
	__BEGIN_TRY

	if (prev >= nPacketHistorySize)
		throw OutOfBoundException();

	// if prev == 0 , return m_PacketHistory[9]
	// if prev == 9 , return m_PacketHistory[0]
	Packet* pPacket = m_PacketHistory[ nPacketHistorySize - prev - 1 ];

	if (pPacket == NULL)
		throw NoSuchElementException("packet history is empty");

	return pPacket;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// 漂沥 菩哦酒捞叼甫 啊柳 啊厘 弥辟狼 菩哦阑 府畔茄促.
//
//////////////////////////////////////////////////////////////////////
Packet* GamePlayer::getOldPacket (PacketID_t packetID)
{
	__BEGIN_TRY

	Packet* pPacket = NULL;
	deque<Packet*>::reverse_iterator ritr = m_PacketHistory.rbegin();

	for (; ritr != m_PacketHistory.rend(); ritr++) 
	{
		if ((*ritr)->getPacketID() == packetID) {
			pPacket = (*ritr);
			break;
		}	
	}

	if (pPacket == NULL)
		throw NoSuchElementException("packet history is empty");

	return pPacket;

	__END_CATCH
}

//--------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------
void GamePlayer::addEvent (Event* pEvent)
{
	__BEGIN_TRY

	m_EventManager.addEvent(pEvent);

	__END_CATCH
}

//--------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------
void GamePlayer::deleteEvent (Event::EventClass EClass)
{
	__BEGIN_TRY

	m_EventManager.deleteEvent(EClass);

	__END_CATCH
}

//--------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------
Event* GamePlayer::getEvent (Event::EventClass EClass)
{
	__BEGIN_TRY

	return m_EventManager.getEvent(EClass);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// get debug string
//
//////////////////////////////////////////////////////////////////////
string GamePlayer::toString () const
{
	__BEGIN_TRY
		
	StringStream msg;
	
	//////////////////////////////////////////////////
	// enter critical section
	//////////////////////////////////////////////////
	__ENTER_CRITICAL_SECTION(m_Mutex)
	
	msg << "GamePlayer(SocketID:" << m_pSocket->getSOCKET() << ",Host:" << m_pSocket->getHost() << ")" ;

	//////////////////////////////////////////////////
	// leave critical section
	//////////////////////////////////////////////////
	__LEAVE_CRITICAL_SECTION(m_Mutex)
	
	return msg.toString();

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// verifySpeed
//
//////////////////////////////////////////////////////////////////////
bool GamePlayer::verifySpeed(Packet* pPacket)
{
	__BEGIN_TRY
	PacketID_t PacketID = pPacket->getPacketID();

	bool SpeedCheck = false;

	Timeval CurrentTime;
	getCurrentTime( CurrentTime );

	//////////////////////////////////////////////////////////////////////////
	// 封包心跳检测 
	// 咖啡 2007-6-25  kf_168@hotmail.com
	//

	if (PacketID == Packet::PACKET_CG_VERIFY_TIME )
	{
		if( m_SpeedVerify.tv_sec == 0 )
		{
			// 如果未获取心跳检测初始化值,则取当前时间+SpeedCheckDelya作为初始值
			// 设置检测通过 SpeedCheck = true;
			m_SpeedVerify.tv_sec = CurrentTime.tv_sec + SpeedCheckDelay;
			
			SpeedCheck = true;
		}
		else
		{
			// 以下开始检测
			// 如果当前时间大于上次检测时间+上偏移值,则检测通过
			if( CurrentTime.tv_sec > m_SpeedVerify.tv_sec - maxTimeGap )
			{
				m_SpeedVerify.tv_sec = CurrentTime.tv_sec + SpeedCheckDelay;

				SpeedCheck = true;
				// 最大错误校验-1,如果当前错误校验超过预设值,则返回假
				m_VerifyCount = max(0, m_VerifyCount-1);
			}
			else
			{
				// 更新下次校验时间,注意这里是取前时间+下次校验时间.
				m_SpeedVerify.tv_sec = CurrentTime.tv_sec + SpeedCheckDelay;

				if( m_VerifyCount > maxVerifyCount )
				{
					SpeedCheck = false;
				}
				else
				{
					SpeedCheck = true;
				}
				m_VerifyCount++;
			}
		}
	}
	//
	// 检测封包发送可能性结束
	// Add by Coffee 2007-6-25 kf_168@hotmail.com
	//////////////////////////////////////////////////////////////////////////
	

	//////////////////////////////////////////////////////////////////////////
	// 增加移动检测封包检测
	// Add by Coffee 2007-6-25 E-mail: kf_168@hotmail.com
	if (PacketID == Packet::PACKET_CG_MOVE)
	{
		if (CurrentTime <= m_MoveSpeedVerify)
		{
			// 使用加速
		}
		//Timeval UseTimer=CurrentTime-m_MoveSpeedVerify;
		tv_sub(&CurrentTime,&m_MoveSpeedVerify);
		double rtt;
		// 以毫秒为单位计算rtt
		rtt =CurrentTime.tv_sec * 1000 + CurrentTime.tv_usec / 1000;
		
		getCurrentTime(m_MoveSpeedVerify);
		//add by viva for notice
		//filelog("MoveLog.txt", "MoveTime:=%.3f ms\n",rtt);
		//end
	}
	
	// End by Coffee 
	//////////////////////////////////////////////////////////////////////////
	
	/*
	// 农府贸狼 胶乔靛甫 罐酒柯促.
	if (m_pCreature == NULL || pPacket == NULL) {
		return true;
	}

	// 痹沥 矫埃 捞傈俊 度 鞍篮 菩哦捞 荐绞锅 朝酒坷搁 立加阑 楼弗促.
	Timeval VerifyTime;
	getCurrentTime(VerifyTime);

	PacketID_t PacketID = pPacket->getPacketID();

	bool SpeedCheck = true;

	if (m_pCreature->isSlayer()) {

		Slayer* pSlayer = dynamic_cast<Slayer*>(m_pCreature);
		Speed_t AttackSpeed = pSlayer->getAttackSpeed();
		BYTE Speed = 0;
		if (AttackSpeed < 33) {
			Speed = 0;
		} else if (AttackSpeed < 67) {
			Speed = 1;
		} else {
			Speed = 2;
		}

		if (PacketID == Packet::PACKET_CG_MOVE) {
			// 捞傈 矫埃捞尔 泅犁 矫埃捞尔 眉农秦辑 歹 狐弗 矫埃俊 菩哦捞 朝酒吭栏搁 捞扒 摹磐促.
			if (VerifyTime <= m_MoveSpeedVerify) {
				SpeedCheck = false;
			}

			getCurrentTime(m_MoveSpeedVerify);
			getCurrentTime(m_AttackSpeedVerify);

			// 促澜俊 公宏啊 啊厘 弧府 朝酒棵 荐 乐绰 啊瓷茄 矫埃阑 历厘秦 敌促.
			// 葛配 荤捞努阑 鸥绊 乐促搁 捞悼加档啊 临绢电促.

			BYTE RealSpeed = 0;
			if (pSlayer->hasRideMotorcycle()) 
			{
				//RealSpeed = 2;
				RealSpeed = 1;
			} 
			else // 葛配荤捞努捞 酒聪促.
			{
				//RealSpeed = 4;
				RealSpeed = 2;
			}

			// 促澜 镜 荐 乐绰 矫埃阑 悸泼茄促.
			m_MoveSpeedVerify.tv_sec += RealSpeed / 10;
			m_MoveSpeedVerify.tv_usec += RealSpeed* 100000;

			m_AttackSpeedVerify.tv_sec += RealSpeed / 10;
			m_AttackSpeedVerify.tv_usec += RealSpeed* 100000;
		} 
		else if (PacketID == Packet::PACKET_CG_ATTACK) 
		{
			if (VerifyTime <= m_AttackSpeedVerify) 
			{
				SpeedCheck = false;
			}
			// 公扁甫 公均阑 甸绊 乐绰瘤 眉农茄促.
			Item* pItem = pSlayer->getWearItem(Slayer::WEAR_RIGHTHAND);
			Item::ItemClass IClass = Item::ITEM_CLASS_SKULL;
			if (pItem != NULL) {
				IClass = pItem->getItemClass();
			} 

			getCurrentTime(m_AttackSpeedVerify);
			getCurrentTime(m_MoveSpeedVerify);

			BYTE RealSpeed = 0;
			// 浇肺快 胶乔靛
			if (Speed == 0) 
			{
				switch (IClass) 
				{
					// 937
					case Item::ITEM_CLASS_SWORD :
						RealSpeed = 9;
						break;
					// 1187
					case Item::ITEM_CLASS_BLADE :
					case Item::ITEM_CLASS_CROSS :
					case Item::ITEM_CLASS_MACE :
						RealSpeed = 11;
						break;
					// 1250
					case Item::ITEM_CLASS_AR :
						RealSpeed = 12;
						break;
					// 1000
					case Item::ITEM_CLASS_SG :
						RealSpeed = 10;
						break;
					// 1375
					case Item::ITEM_CLASS_SR :
						RealSpeed = 13;
						break;
					// 1000
					case Item::ITEM_CLASS_SMG :
						RealSpeed = 10;
						break;
					// 扁夯 傍拜 875
					default :
						RealSpeed = 8;
						break;
				}
			} 
			else if (Speed == 1) // 畴钢 胶乔靛
			{
				switch (IClass) 
				{
					// 812
					case Item::ITEM_CLASS_SWORD :
						RealSpeed = 8;
						break;
					// 1062
					case Item::ITEM_CLASS_BLADE :
					case Item::ITEM_CLASS_CROSS :
					case Item::ITEM_CLASS_MACE :
						RealSpeed = 10;
						break;
					// 875
					case Item::ITEM_CLASS_AR :
						RealSpeed = 8;
						break;
					// 1125
					case Item::ITEM_CLASS_SG :
						RealSpeed = 11;
						break;
					// 1250
					case Item::ITEM_CLASS_SR :
						RealSpeed = 12;
						break;
					// 875
					case Item::ITEM_CLASS_SMG :
						RealSpeed = 8;
						break;
					// 扁夯 傍拜 875
					default :
						RealSpeed = 8;
						break;

				}
			} 
			else // 菩胶飘 胶乔靛
			{
				switch (IClass) 
				{
					// 687
					case Item::ITEM_CLASS_SWORD :
						RealSpeed = 6;
						break;
					// 938
					case Item::ITEM_CLASS_BLADE :
					case Item::ITEM_CLASS_CROSS :
					case Item::ITEM_CLASS_MACE :
						RealSpeed = 9;
						break;
					// 750
					case Item::ITEM_CLASS_AR :
						RealSpeed = 7;
						break;
					// 1000
					case Item::ITEM_CLASS_SG :
						RealSpeed = 10;
						break;
					// 1125
					case Item::ITEM_CLASS_SR :
						RealSpeed = 11;
						break;
					// 750
					case Item::ITEM_CLASS_SMG :
						RealSpeed = 7;
						break;
					// 875
					default :
						RealSpeed = 8;
						break;
				}
			}

			// 胶乔靛 肯拳 沥氓
			RealSpeed -= 2;

			m_AttackSpeedVerify.tv_sec += RealSpeed / 10;
			m_AttackSpeedVerify.tv_usec += ((RealSpeed % 10)* 100000);

			m_MoveSpeedVerify.tv_sec += RealSpeed / 10;
			m_MoveSpeedVerify.tv_usec += ((RealSpeed % 10)* 100000);

		} else if (PacketID == Packet::PACKET_CG_SKILL_TO_OBJECT || PacketID == Packet::PACKET_CG_SKILL_TO_SELF || PacketID == Packet::PACKET_CG_SKILL_TO_TILE) {

		} else {
			SpeedCheck = true;
		}
	} 
	else if (m_pCreature->isVampire()) 
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(m_pCreature);
		Speed_t AttackSpeed = pVampire->getAttackSpeed();

		BYTE Speed = 0;
		if (AttackSpeed < 33) 
		{
			Speed = 0;
		} 
		else if (AttackSpeed < 67) 
		{
			Speed = 1;
		} 
		else 
		{
			Speed = 2;
		}

		if (PacketID == Packet::PACKET_CG_MOVE) 
		{
			// 捞傈 矫埃捞尔 泅犁 矫埃捞尔 眉农秦辑 歹 狐弗 矫埃俊 菩哦捞 朝酒吭栏搁 捞扒 摹磐促.
			if (VerifyTime <= m_MoveSpeedVerify) 
			{
				SpeedCheck = false;
			}

			getCurrentTime(m_MoveSpeedVerify);
			getCurrentTime(m_AttackSpeedVerify);

			BYTE RealSpeed = 0;
			// 促澜俊 公宏啊 啊厘 弧府 朝酒棵 荐 乐绰 啊瓷茄 矫埃阑 历厘秦 敌促.
			// 冠零 函脚阑 窍绊 乐促搁 加档啊 弧扼柳促. 檬寸 匙 鸥老阑 捞悼 茄促.
			if (pVampire->isFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_BAT)) 
			{
				//RealSpeed = 2;
				RealSpeed = 1;
			} 
			else // 畴钢 惑怕俊急 檬寸 滴鸥老阑 捞悼茄促.
			{
				//RealSpeed = 4;
				RealSpeed = 2;
			}

			m_MoveSpeedVerify.tv_sec += (RealSpeed / 10);
			m_AttackSpeedVerify.tv_sec += (RealSpeed / 10);

			m_MoveSpeedVerify.tv_usec += (RealSpeed* 100000);
			m_AttackSpeedVerify.tv_usec += (RealSpeed* 100000);
		} 
		else if (PacketID == Packet::PACKET_CG_ATTACK) 
		{
			if (VerifyTime <= m_AttackSpeedVerify) 
			{
				SpeedCheck = false;
			}

			getCurrentTime(m_AttackSpeedVerify);
			getCurrentTime(m_MoveSpeedVerify);

			BYTE RealSpeed = 0;
			if (Speed == 0) // 浇肺快 胶乔靛 875
			{
				RealSpeed = 8;
			} 
			else if (Speed == 1) // 畴钢 胶乔靛 875
			{
				RealSpeed = 8;
			} 
			else // 菩胶飘 胶乔靛 812
			{
				RealSpeed = 8;
			}

			// 胶乔靛 肯拳 沥氓
			RealSpeed -= 2;

			m_AttackSpeedVerify.tv_sec += RealSpeed / 10;
			m_AttackSpeedVerify.tv_usec += ((RealSpeed % 10)* 100000);

			m_MoveSpeedVerify.tv_sec += RealSpeed / 10;
			m_MoveSpeedVerify.tv_usec += ((RealSpeed % 10)* 100000);
		} 
		else if (PacketID == Packet::PACKET_CG_SKILL_TO_OBJECT || 
				  PacketID == Packet::PACKET_CG_SKILL_TO_SELF   || 
				  PacketID == Packet::PACKET_CG_SKILL_TO_TILE) 
		{
		} 
		else 
		{
			SpeedCheck = true;
		}
	} 
	else 
	{
	}
	*/

	return SpeedCheck;

	__END_CATCH
}

void GamePlayer::loadSpecialEventCount(void)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;
	Result*    pResult = NULL;

	BEGIN_DB
	{
//		pStmt   = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt   = g_pDatabaseManager->getDistConnection( "PLAYER_DB" )->createStatement();

		pResult = pStmt->executeQuery("SELECT SpecialEventCount FROM Player WHERE PlayerID='%s'", m_ID.c_str());

		if (pResult->getRowCount() != 0)
		{
			pResult->next();
			m_SpecialEventCount = pResult->getDWORD(1);
		}
		else
		{
			SAFE_DELETE(pStmt);
			throw ("GamePlayer::loadSpecialEventCount() : unable to dispatch data");
			return;
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt);

	__END_CATCH
}

void GamePlayer::saveSpecialEventCount(void)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getDistConnection("PLAYER_DB")->createStatement();
//		pStmt = g_pDatabaseManager->getConnection( (int)Thread::self() )->createStatement();

		pStmt->executeQuery("UPDATE Player SET SpecialEventCount=%d WHERE PlayerID='%s'", m_SpecialEventCount, m_ID.c_str());
		SAFE_DELETE(pStmt);	
	}
	END_DB(pStmt);

	__END_CATCH
}

bool    GamePlayer::sendBillingLogin() 
{
	__BEGIN_TRY

	if (!m_ID.empty() && m_ID!="NONE")
	{
		Timeval currentTime;
		getCurrentTime(currentTime);

		if (currentTime > m_BillingNextLoginRequestTime)
		{
			g_pBillingPlayerManager->sendPayLogin( this );

			Timeval afterTime;
			getCurrentTime( afterTime );

			// 1檬 捞惑 吧府搁 肺弊 巢变促.
			if ( afterTime.tv_sec > currentTime.tv_sec + 1 )
			{
				filelog( "billingLoginTime.txt", "PlayerID : %s, CallTime : %d sec, Try : %d", m_ID.c_str(), (int)(afterTime.tv_sec - currentTime.tv_sec), m_BillingLoginRequestCount );
			}

			// PayLogin 夸没茄 雀荐 扁撅
			m_BillingLoginRequestCount ++;

			// 60檬 饶 促矫 眉农茄促.
			m_BillingNextLoginRequestTime.tv_sec = currentTime.tv_sec + 60;
		}

		return true;
	}

	return false;

	__END_CATCH
}

void GamePlayer::sendCBillingPayInfo()
{
	__BEGIN_TRY

	char m[200];
	if ( m_CBPlayerType == CBILLING_PLAYER_TYPE_MONTHLY )
	{
		VSDate currentDate;
		currentDate = VSDate::currentDate();

		sprintf( m, g_pStringPool->c_str( STRID_CB_MONTHLY_PLAYER ),
						m_CBEndDateTime.date().year(),
						m_CBEndDateTime.date().month(),
						m_CBEndDateTime.date().day(),
						currentDate.year(),
						currentDate.month(),
						currentDate.day() );

		GCSystemMessage msg;
		msg.setMessage( m );

		sendPacket( &msg );
	}
	else if ( m_CBPlayerType == CBILLING_PLAYER_TYPE_POINT )
	{
		sprintf( m, g_pStringPool->c_str( STRID_CB_POINT_PLAYER ), m_CBLeftTime / 10 );

		GCSystemMessage msg;
		msg.setMessage( m );

		sendPacket( &msg );
	}

	__END_CATCH
}

// 鞠龋拳 内靛甫 汲沥茄促.
void GamePlayer::setEncryptCode()
{
    __BEGIN_TRY

#ifdef __USE_ENCRYPTER__
	Assert(m_pCreature!=NULL);

	// 老窜篮 ObjectID甫 捞侩茄促.
	//ObjectID_t 	objectID 	= m_pCreature->getObjectID();

	// 粮喊肺 包府甫 窍档废 荐沥茄促.
//	ZoneID_t 	zoneID 		= m_pCreature->getZone()->getZoneID();
//	static int	serverID	= g_pConfig->getPropertyInt("ServerID");

//	if (objectID!=0)
//	{
		//uchar code = (uchar)(objectID / zoneID + objectID);
		//uchar code = (uchar)( ( ( zoneID >> 8 ) ^ zoneID ) ^ ( ( serverID + 1 ) << 4 ) );
		uchar code = m_pCreature->getZone()->getEncryptCode();

#ifdef __ACTIVE_SERVICE_DEADLINE__
		// 辑滚 官焊 父甸扁 内靛
		VSDate date = VSDate::currentDate();
		// 2003斥 1岿 捞惑牢 版快: 2003, 0
		if (date.year()>=DEADLINE_YEAR && date.month()>DEADLINE_MONTH)
			code += (date.year()+date.month())/11;
#endif

		SocketEncryptOutputStream* pEOS = dynamic_cast<SocketEncryptOutputStream*>(m_pOutputStream);
		Assert(pEOS!=NULL);

		SocketEncryptInputStream* pEIS = dynamic_cast<SocketEncryptInputStream*>(m_pInputStream);
		Assert(pEIS!=NULL);

		pEOS->setEncryptCode(code);
		pEIS->setEncryptCode(code);
//	}
#endif

	__END_CATCH
}

void GamePlayer::kickPlayer( uint nSeconds, uint KickMessageType )
{
	__BEGIN_TRY

	// 捞固 EventKick 捞 乐促搁 公矫茄促.
	if ( m_EventManager.getEvent( Event::EVENT_CLASS_KICK ) != NULL )
		return;

	EventKick* pEventKick = new EventKick( this );
	pEventKick->setDeadline( nSeconds * 10 );
	addEvent( pEventKick );

	// 割 檬饶俊 漏赴促..绊 焊郴霖促.
	GCKickMessage gcKickMessage;
	gcKickMessage.setType( KickMessageType );
	gcKickMessage.setSeconds( nSeconds );
	sendPacket( &gcKickMessage );

	__END_CATCH
}

//////////////////////////////////////////////////////////////////
// PaySystem 包访
//////////////////////////////////////////////////////////////////
bool GamePlayer::loginPayPlay( PayType payType, const string& PayPlayDate, int PayPlayHours, uint payPlayFlag, const string& ip, const string& playerID )
{
	__BEGIN_TRY
#ifdef __CONNECT_BILLING_SYSTEM__
	return BillingPlayerInfo::isBillingPlayAvaiable();
#else
	return PaySystem::loginPayPlay( payType, PayPlayDate, PayPlayHours, payPlayFlag, ip, playerID );
#endif
	__END_CATCH
}

bool GamePlayer::loginPayPlay( const string& ip, const string& playerID )
{
	__BEGIN_TRY
#ifdef __CONNECT_BILLING_SYSTEM__
	return BillingPlayerInfo::isBillingPlayAvaiable();
#else
	bool bRet = PaySystem::loginPayPlay( ip, playerID );

	if ( bRet )
		setPCRoomLottoStartTime();

	return bRet;
#endif
	__END_CATCH
}

bool GamePlayer::updatePayPlayTime( const string& playerID, const VSDateTime& currentDateTime, const Timeval& currentTime )
{
	__BEGIN_TRY
#ifdef __CONNECT_BILLING_SYSTEM__
	return BillingPlayerInfo::isBillingPlayAvaiable();
#else
	checkPCRoomLotto( currentTime );

	return PaySystem::updatePayPlayTime( playerID, currentDateTime, currentTime );
#endif
	__END_CATCH
}

void GamePlayer::logoutPayPlay( const string& playerID, bool bClear, bool bDecreaseTime )
{
	__BEGIN_TRY
#ifdef __CONNECT_BILLING_SYSTEM__
	if ( !BillingPlayerInfo::isBillingPlayAvaiable() )
		setPremiumPlay( false );
#else
	savePCRoomLottoTime();

	PaySystem::logoutPayPlay( playerID, bClear, bDecreaseTime );
#endif
	__END_CATCH
}

bool GamePlayer::isPayPlaying() const
{
#ifdef __CONNECT_BILLING_SYSTEM__
	return BillingPlayerInfo::isBillingPlayAvaiable();
#elif defined(__CONNECT_CBILLING_SYSTEM__)
	return CBillingPlayerInfo::isPayPlayer();
#elif !defined(__PAY_SYSTEM_ZONE__) && !defined(__PAY_SYSTEM_LOGIN__) && !defined(__PAY_SYSTEM_FREE_LIMIT__)
	// if there is no Pay defines, all users are pay player
	return true;
#else
	return PaySystem::isPayPlaying();
#endif
}

//////////////////////////////////////////////////////////////////////////////
//
// add LogoutPlayerdata
//
// 立加磊 烹拌甫 困秦辑 
// UserInfo DB狼 LogoutPlayerData俊 Logout茄 荤侩磊甫 眠啊茄促.
//
//////////////////////////////////////////////////////////////////////////////
void addLogoutPlayerData(Player* pPlayer)
{

	Statement* pStmt = NULL;

	pStmt = g_pDatabaseManager->getUserInfoConnection()->createStatement();

	// 蜡历 烹拌 包访 沥焊甫 涝仿茄促.
	BEGIN_DB
	{
		string ID = pPlayer->getID();
		string ip = pPlayer->getSocket()->getHost();

		// 刚历 泅犁 矫埃阑 掘绢辰促.
		int year, month, day, hour, minute, second;
		getCurrentTimeEx(year, month, day, hour, minute, second);
		string currentDT = VSDateTime::currentDateTime().toDateTime();

		StringStream sql;
		sql << "INSERT INTO USERINFO.LogoutPlayerData (PlayerID,IP,Date,Time) VALUES ('"
			<< ID << "','" << ip << "','"
			<< currentDT.substr( 0, 10 ).c_str() << "','"
			<< currentDT.substr( 11 ).c_str() << "')";

		pStmt->executeQueryString(sql.toString());

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
}

void GamePlayer::setPCRoomLottoStartTime()
{
	if ( !g_pVariableManager->isPCRoomLottoEvent() )
		return;

	if ( !m_bPCRoomPlay )
		return;

	m_PCRoomLottoStartTime.tv_sec = m_PayPlayStartTime.tv_sec - m_PCRoomLottoSumTime;
}

void GamePlayer::savePCRoomLottoTime()
{
	if ( !g_pVariableManager->isPCRoomLottoEvent() )
		return;

	if ( !m_bPCRoomPlay )
		return;

	Timeval currentTime;
	getCurrentTime( currentTime );

	m_PCRoomLottoSumTime = currentTime.tv_sec - m_PCRoomLottoStartTime.tv_sec;
	m_PCRoomLottoStartTime.tv_sec = 0;
}

void GamePlayer::checkPCRoomLotto( const Timeval& currentTime )
{
	if ( !g_pVariableManager->isPCRoomLottoEvent() )
		return;

	if ( !m_bPCRoomPlay )
		return;

	if ( m_PCRoomLottoStartTime.tv_sec == 0 )
	{
		m_PCRoomLottoStartTime.tv_sec = currentTime.tv_sec - m_PCRoomLottoSumTime;
	}

	int time = currentTime.tv_sec - m_PCRoomLottoStartTime.tv_sec;	

	if ( time >= PCRoomLottoSec )
	{
		giveLotto();

		// 促矫 矫埃阑 檬扁拳茄促.
		m_PCRoomLottoStartTime.tv_sec = currentTime.tv_sec;
		m_PCRoomLottoSumTime = 0;
	}
}

void GamePlayer::giveLotto()
{
	if ( m_pCreature == NULL )
		return;

	Statement* pStmt = NULL;
	Result* pResult = NULL;

	BEGIN_DB
	{
		static uint DimensionID	= g_pConfig->getPropertyInt( "Dimension" );
		static uint WorldID		= g_pConfig->getPropertyInt( "WorldID" );
		string PlayerID		= getID();
		string Name			= m_pCreature->getName();
		Race_t Race			= m_pCreature->getRace();
		int Amount			= 0;
		pStmt = g_pDatabaseManager->getDistConnection("PLAYER_DB")->createStatement();
		pResult = pStmt->executeQuery( "SELECT Amount FROM PCRoomLottoObject WHERE PlayerID = '%s' AND Name = '%s' AND DimensionID = %u AND WorldID = %u",
										PlayerID.c_str(), Name.c_str(), DimensionID, WorldID );

		if ( pResult->next() )
		{
			Amount = pResult->getInt( 1 );

			if ( Amount < PCRoomLottoMaxAmount )
			{
				pStmt->executeQuery( "UPDATE PCRoomLottoObject SET Amount = %d WHERE PlayerID = '%s' AND Name = '%s' AND DimensionID = %u AND WorldID = %u",
										Amount + 1, PlayerID.c_str(), Name.c_str(), DimensionID, WorldID );
			}
		}
		else
		{
			// 汗鼻捞 绝菌促. 货肺 持绢霖促.
			pStmt->executeQuery( "INSERT INTO PCRoomLottoObject VALUES ( 0, %u, '%s', %u, %u, '%s', %u, 1 )",
									m_PCRoomID, PlayerID.c_str(), DimensionID, WorldID, Name.c_str(), Race );
		}

		if ( Amount < PCRoomLottoMaxAmount )
		{
			char msg[100];
			sprintf( msg, g_pStringPool->c_str( STRID_GIVE_LOTTO ), Amount + 1 ); 

			GCSystemMessage gcMsg;
			gcMsg.setMessage( msg );
			sendPacket( &gcMsg );

			if ( Amount >= PCRoomLottoMaxAmount - 1 )
			{
				gcMsg.setMessage( g_pStringPool->getString( STRID_CANNOT_GIVE_LOTTO ) );
				sendPacket( &gcMsg );
			}
		}
	}
	END_DB( pStmt )
}

bool GamePlayer::startPacketLog( uint sec )
{
	if ( m_pCreature == NULL )
		return false;

	m_bPacketLog = true;
	getCurrentTime( m_PacketLogEndTime );
	m_PacketLogEndTime.tv_sec += sec;

	char filename[100];
	sprintf( filename, "log/%s.log", m_pCreature->getName().c_str() );
	m_PacketLogFileName = filename;

	return true;
}

void GamePlayer::logLoginoutDateTime()
{
	if ( m_pCreature == NULL )
		return;

	// DimensionID 备窍扁
	uint dimensionID = g_pConfig->getPropertyInt("Dimension");
	if ( g_pConfig->getPropertyInt("IsNetMarble") == 0 )
	{
		// 齿付喉 老 版快浚 2
		dimensionID = 2;
	}

	// WorldID
	uint worldID = g_pConfig->getPropertyInt("WorldID");

	// 辆练 内靛
	uint racecode;
	uint str,dex,inte;
	if ( m_pCreature->isSlayer() )
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(m_pCreature);
		Assert( pSlayer != NULL );

		racecode = (uint)pSlayer->getHighestSkillDomain();

		str = pSlayer->getSTR();
		dex = pSlayer->getDEX();
		inte = pSlayer->getINT();
	}
	else if ( m_pCreature->isVampire() )
	{
		// 轨颇捞绢绰  10
		racecode = 10;

		Vampire* pVampire = dynamic_cast<Vampire*>(m_pCreature);
		Assert( pVampire != NULL );

		str = pVampire->getSTR();
		dex = pVampire->getDEX();
		inte = pVampire->getINT();
	}
	else if ( m_pCreature->isOusters() )
	{
		// 酒快胶磐令绰 20
		racecode = 20;

		Ousters* pOusters = dynamic_cast<Ousters*>(m_pCreature);
		Assert( pOusters != NULL );

		str = pOusters->getSTR();
		dex = pOusters->getDEX();
		inte = pOusters->getINT();
	}
	else
	{
		return;
	}

	// 饭骇
	uint level = (uint)m_pCreature->getLevel();

	// 肺弊酒眶 矫埃. 泅犁 矫埃
	VSDateTime logoutDateTime = VSDateTime::currentDateTime();

	// filename
	char filename[20];
	sprintf( filename, "log/%s.txt", logoutDateTime.toStringforWeb().c_str() );

	try
	{
		ofstream file( filename, ios::out | ios::app );
		file << dimensionID << "\t" << worldID << "\t" << m_ID << "\t"
			 << m_pCreature->getName() << "\t" << racecode << "\t"
			 << level << "\t" << str << "\t" << dex << "\t" << inte << "\t"
			 << m_LoginDateTime.toDateTime() << "\t"
			 << logoutDateTime.toDateTime() << endl;
		file.close();
	}
	catch (...)
	{
	}
}

