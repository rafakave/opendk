//////////////////////////////////////////////////////////////////////////////
// Filename    : CGLotterySelectHandler.cpp
// Written By  :
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGLotterySelect.h"

#ifdef __GAME_SERVER__

#include "DB.h"
#include "GamePlayer.h"
#include "PlayerCreature.h"
#include "NPC.h"
#include "ItemUtil.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "ZoneGroupManager.h"

#include "Item.h"
#include "ItemFactoryManager.h"
#include "MonsterInfo.h"

#include "PacketUtil.h"
#include "Properties.h"

#include "GameWorldInfoManager.h"

#include "mission/QuestManager.h"
#include "mission/EventQuestAdvance.h"

#include "CGSay.h"
#include "GCNoticeEvent.h"
#include "GCDeleteInventoryItem.h"
#include "GCNotifyWin.h"
#include "GCCreateItem.h"

#include <cstdio>

#endif	// __GAME_SERVER__

void CGLotterySelectHandler::execute (CGLotterySelect* pPacket , Player* pPlayer)
	 
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_SERVER__
	// 取消完成任务不给物品限制
	//return;

	GamePlayer* pGP = dynamic_cast<GamePlayer*>( pPlayer );
	Assert( pGP != NULL );

	Creature* pCreature = pGP->getCreature();
	Assert( pCreature != NULL );
		
	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
	Assert( pPC != NULL );

	filelog( "EventQuest.log", "CGLotterySelectHandler : got [%d:%d:%d] from %s", pPacket->getType(), pPacket->getGiftID(), pPacket->getQuestLevel(),
			pPC->getName().c_str() );


	
	switch ( pPacket->getType() )
	{
		case TYPE_SELECT_LOTTERY:
			{
				// 牢亥俊辑 涅胶飘 酒捞袍 昏力
				QuestID_t qID;
				EventQuestAdvance::Status status = pPC->getQuestManager()->getEventQuestAdvanceManager()->getStatus( pPacket->getQuestLevel() );
				int ownerQuestLevel = pPC->getQuestManager()->getEventQuestAdvanceManager()->getQuestLevel();
				if ( 
					( ownerQuestLevel > pPacket->getQuestLevel() && status == EventQuestAdvance::EVENT_QUEST_ADVANCED ) ||	
					( pPacket->getQuestLevel() == 4 &&  ownerQuestLevel== -1 ) ||
					pPC->getQuestManager()->successEventQuest( pPacket->getQuestLevel(), qID ) )
				{
					pPC->getQuestManager()->getEventQuestAdvanceManager()->rewarded( pPacket->getQuestLevel() );
					pPC->getQuestManager()->getEventQuestAdvanceManager()->save();
					pPC->getQuestManager()->questRewarded( qID );
					pPC->sendCurrentQuestInfo();

					list<Item*> iList;
					pPC->getInventory()->clearQuestItem(iList);

					list<Item*>::iterator itr = iList.begin();
					list<Item*>::iterator endItr = iList.end();

					for ( ; itr != endItr ; ++itr )
					{
						GCDeleteInventoryItem gcDII;
						gcDII.setObjectID( (*itr)->getObjectID() );
						pPC->getPlayer()->sendPacket( &gcDII );
						(*itr)->destroy();
						SAFE_DELETE( *itr );
					}

					iList.clear();
				}
				else
				{
					filelog( "EventBug.txt", "CGLotterySelectHandler : 汗鼻 急琶捞 朝扼吭绰单 肯丰茄 涅胶飘啊 绝促. -_-; %s[%d:%d]",
							pPC->getName().c_str(), pPacket->getQuestLevel(), pPacket->getGiftID() );

					return;
				}

				GCNoticeEvent gcNE;
				gcNE.setCode( NOTICE_EVENT_RESULT_LOTTERY );
				if ( bWinPrize( pPacket->getGiftID(), pPacket->getQuestLevel() ) ) 
				{
					// PlayerCreature 俊 沥焊甫 历厘茄促
					pPC->setLotto(true);
					pPC->setLottoRewardID( pPacket->getGiftID() );
					pPC->setLottoQuestLevel( pPacket->getQuestLevel() );
					gcNE.setParameter( (uint)1 );
				}
				else
				{
					// PlayerCreature 俊 沥焊甫 历厘茄促
					pPC->setLotto(false);
					pPC->setLottoRewardID( pPacket->getGiftID() );
					pPC->setLottoQuestLevel( pPacket->getQuestLevel() );
					gcNE.setParameter( (uint)0 );
				}
				pGP->sendPacket( &gcNE );

				filelog( "EventQuest.log", "CGLotterySelectHandler : %d to %s", gcNE.getParameter(), pPC->getName().c_str() );
			}
			break;
		case TYPE_FINISH_SCRATCH:
			{
				// 寸梅等 版快 叼厚俊 历厘
				if ( pPC->isLotto() )
				{
					// 促矫 false 肺 父甸绢拎具窃.
					// 酒丛 淬锅 涅胶飘俊辑 公炼扒 寸梅栏肺 贸府登聪 ;;
					pPC->setLotto(false);

					Statement* pStmt = NULL;

					BEGIN_DB
					{
						pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

						pStmt->executeQuery( "INSERT INTO EventQuestRewardRecord (PlayerID, RewardID, Time, RealPlayerID) VALUES ( '%s', %d, now(), '%s' )",
								pCreature->getName().c_str(),
								pPC->getLottoRewardID(),
								pPC->getPlayer()->getID().c_str() );

						SAFE_DELETE(pStmt);
					}
					END_DB(pStmt)

					// 捞率 辑滚俊 宏肺靛 某胶飘 窍绊 (allworld 绰 秦寸 辑滚绰 贸府 救窃)
					GCNotifyWin gcNW;
					gcNW.setGiftID( pPC->getLottoRewardID() );
					gcNW.setName( pCreature->getName() );

					g_pZoneGroupManager->broadcast( &gcNW );

					// 傈 岿靛俊 宏肺靛某胶飘秦霖促 
					char sCommand[200];
					string worldName = g_pGameWorldInfoManager->getGameWorldInfo(g_pConfig->getPropertyInt( "WorldID" ))->getName();
					sprintf( sCommand, "*allworld *command NotifyWin %s(%s) %lu", pCreature->getName().c_str(), worldName.c_str(), pPC->getLottoRewardID() );
					CGSayHandler::opworld( NULL, sCommand, 0, false );

				}
				else
				{
					// 酒聪搁 弊成 涅胶飘 酒捞袍父 牢亥俊 持绢林搁 登绰淀
					Item::ItemClass iClass;
					ItemType_t iType;
					list<OptionType_t> oList;
					bool isTimeLimit = false;
					bool isLairItem = false;
					bool isUnique = false;
					MonsterType_t masterType;

					// 第一个任务不给任何物品
// 					if (pPC->getLottoQuestLevel()== 0 )
// 					{
// 						return;
// 					}
					switch( pPC->getLottoQuestLevel() )
//					switch( pPC->getQuestManager()->getEventQuestAdvanceManager()->getQuestLevel() )
					{
						case 0:
							{
								// 第一个任务不给任何物品
								return;
								static const string options1[] =
								{
									"STR+2",
									"DEX+2",
									"INT+2",
									"ASPD+2",
									"HP+2"
								};

								static const string options2[] =
								{
									"STR+3",
									"DEX+3",
									"INT+3",
									"ASPD+3",
									"HP+3"
								};
								if ( pPC->isSlayer() )
								{
									Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
									QuestGrade_t qGrade = pSlayer->getTotalAttr( ATTR_BASIC );

									iClass = Item::ITEM_CLASS_RING;

									if ( qGrade < 131 )
									{
										iType = 1;
										makeOptionList( options1[ rand()%5 ], oList );
									}
									else if ( qGrade < 211 )
									{
										iType = 2;
										makeOptionList( options1[ rand()%5 ], oList );
									}
									else if ( qGrade < 271 )
									{
										iType = 3;
										makeOptionList( options2[ rand()%5 ], oList );
									}
									else if ( qGrade < 300 )
									{
										iType = 4;
										makeOptionList( options2[ rand()%5 ], oList );
									}
									else
									{
										iType = 5;
										makeOptionList( options2[ rand()%5 ], oList );
									}
								}
								else if ( pPC->isVampire() )
								{
									Vampire* pVampire = dynamic_cast<Vampire*>(pPC);
									Level_t level = pVampire->getLevel();

									iClass = Item::ITEM_CLASS_VAMPIRE_RING;

									if ( level < 31 )
									{
										iType = 1;
										makeOptionList( options1[ rand()%5 ], oList );
									}
									else if ( level < 51 )
									{
										iType = 2;
										makeOptionList( options1[ rand()%5 ], oList );
									}
									else if ( level < 71 )
									{
										iType = 3;
										makeOptionList( options2[ rand()%5 ], oList );
									}
									else if ( level < 91 )
									{
										iType = 4;
										makeOptionList( options2[ rand()%5 ], oList );
									}
									else
									{
										iType = 5;
										makeOptionList( options2[ rand()%5 ], oList );
									}
								}
								else if ( pPC->isOusters() )
								{
									Ousters* pOusters = dynamic_cast<Ousters*>(pPC);
									Level_t level = pOusters->getLevel();

									iClass = Item::ITEM_CLASS_OUSTERS_RING;

									if ( level < 31 )
									{
										iType = 1;
										makeOptionList( options1[ rand()%5 ], oList );
									}
									else if ( level < 51 )
									{
										iType = 2;
										makeOptionList( options1[ rand()%5 ], oList );
									}
									else if ( level < 71 )
									{
										iType = 3;
										makeOptionList( options2[ rand()%5 ], oList );
									}
									else if ( level < 91 )
									{
										iType = 4;
										makeOptionList( options2[ rand()%5 ], oList );
									}
									else
									{
										iType = 5;
										makeOptionList( options2[ rand()%5 ], oList );
									}
								}
							}
							break;
						case 1:
							{
								static const string oSlayer1[] =
								{
									"DAM+2",
									"VIS+3",
									"MP+2",
									"LUCK+1",
									"HP+2"
								};
								static const string oSlayer2[] =
								{
									"DAM+3",
									"VIS+3",
									"MP+3",
									"LUCK+2",
									"HP+3"
								};
								static const string oVampire1[] =
								{
									"DAM+2",
									"VIS+3",
									"ASPD+2",
									"LUCK+1",
									"HP+2"
								};
								static const string oVampire2[] =
								{
									"DAM+3",
									"VIS+3",
									"ASPD+3",
									"LUCK+2",
									"HP+3"
								};
								if ( pPC->isSlayer() )
								{
									Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
									QuestGrade_t qGrade = pSlayer->getTotalAttr( ATTR_BASIC );

									iClass = Item::ITEM_CLASS_RING;

									if ( qGrade < 131 )
									{
										iType = 2;
										makeOptionList( oSlayer1[ rand()%5 ], oList );
									}
									else if ( qGrade < 211 )
									{
										iType = 3;
										makeOptionList( oSlayer1[ rand()%5 ], oList );
									}
									else if ( qGrade < 271 )
									{
										iType = 4;
										makeOptionList( oSlayer2[ rand()%5 ], oList );
									}
									else if ( qGrade < 300 )
									{
										iType = 5;
										makeOptionList( oSlayer2[ rand()%5 ], oList );
									}
									else
									{
										iType = 6;
										makeOptionList( oSlayer2[ rand()%5 ], oList );
									}
								}
								else if ( pPC->isVampire() )
								{
									Vampire* pVampire = dynamic_cast<Vampire*>(pPC);
									Level_t level = pVampire->getLevel();

									iClass = Item::ITEM_CLASS_VAMPIRE_RING;
									
									if ( level < 31 )
									{
										iType = 2;
										makeOptionList( oVampire1[ rand()%5 ], oList );
									}
									else if ( level < 51 )
									{
										iType = 3;
										makeOptionList( oVampire1[ rand()%5 ], oList );
									}
									else if ( level < 71 )
									{
										iType = 4;
										makeOptionList( oVampire2[ rand()%5 ], oList );
									}
									else if ( level < 91 )
									{
										iType = 5;
										makeOptionList( oVampire2[ rand()%5 ], oList );
									}
									else
									{
										iType = 6;
										makeOptionList( oVampire2[ rand()%5 ], oList );
									}
								}
								else if ( pPC->isOusters() )
								{
									Ousters* pOusters = dynamic_cast<Ousters*>(pPC);
									Level_t level = pOusters->getLevel();

									iClass = Item::ITEM_CLASS_OUSTERS_RING;
									
									if ( level < 31 )
									{
										iType = 2;
										makeOptionList( oVampire1[ rand()%5 ], oList );
									}
									else if ( level < 51 )
									{
										iType = 3;
										makeOptionList( oVampire1[ rand()%5 ], oList );
									}
									else if ( level < 71 )
									{
										iType = 4;
										makeOptionList( oVampire2[ rand()%5 ], oList );
									}
									else if ( level < 91 )
									{
										iType = 5;
										makeOptionList( oVampire2[ rand()%5 ], oList );
									}
									else
									{
										iType = 6;
										makeOptionList( oVampire2[ rand()%5 ], oList );
									}
								}
							}
							break;
						case 2:
							{
								isLairItem = true;
								masterType = 432;
							}
							break;
						case 3:
							{
								isLairItem = true;
								masterType = 433;
							}
							break;
						case 4:
							{
								isTimeLimit = true;
								if ( pPC->isSlayer() )
								{
									isUnique = true;
									static const Item::ItemClass iClasses[] =
									{
										Item::ITEM_CLASS_COAT,
										Item::ITEM_CLASS_TROUSER,
										Item::ITEM_CLASS_GLOVE,
										Item::ITEM_CLASS_HELM,
										Item::ITEM_CLASS_SHOES,
//										Item::ITEM_CLASS_BELT,
										Item::ITEM_CLASS_NECKLACE,
										Item::ITEM_CLASS_BRACELET
									};
									static const ItemType_t iTypes[] =
									{
										16,
										16,
										8,
										9,
										7,
//										4,
										10,
										10
									};

									int index = rand() % 7;
									iClass = iClasses[index];
									iType = iTypes[index];
								}
								else if ( pPC->isVampire() )
								{
									isUnique = true;
									static const Item::ItemClass iClasses[] =
									{
										Item::ITEM_CLASS_VAMPIRE_COAT,
										Item::ITEM_CLASS_VAMPIRE_WEAPON,
										Item::ITEM_CLASS_VAMPIRE_RING,
										Item::ITEM_CLASS_VAMPIRE_NECKLACE,
										Item::ITEM_CLASS_VAMPIRE_BRACELET,
										Item::ITEM_CLASS_VAMPIRE_AMULET,
										Item::ITEM_CLASS_VAMPIRE_EARRING
									};
									static const ItemType_t iTypes[] =
									{
										12,
										15,
										10,
										10,
										9,
										10,
										10
									};
									int index = rand() % 7;
									iClass = iClasses[index];
									iType = iTypes[index];
								}
								else if ( pPC->isOusters() )
								{
									static const Item::ItemClass iClasses[] =
									{
										Item::ITEM_CLASS_OUSTERS_COAT,
										Item::ITEM_CLASS_OUSTERS_CIRCLET,
										Item::ITEM_CLASS_OUSTERS_ARMSBAND,
										Item::ITEM_CLASS_OUSTERS_BOOTS,
										Item::ITEM_CLASS_OUSTERS_PENDENT,
										Item::ITEM_CLASS_OUSTERS_RING
									};
									static const ItemType_t iTypes[] =
									{
										7,
										9,
										9,
										7,
										9,
										9
									};
									static const string options[] =
									{
										"DAM+3",
										"ASPD+3",
										"LUCK+2",
										"HP+9",
										"STR+3",
										"DEX+3",
										"INT+3",
										"ATTR+2",
										"RES+3",
										"MP+4"
									};
									int index = rand() % 6;
									iClass = iClasses[index];
									iType = iTypes[index];

									int option1 = rand()%10;
									int option2 = rand()%10;

									while ( option1 == option2 ) option2 = rand()%10;

									makeOptionList( options[ option1 ] + "," + options[ option2 ], oList );
								}
							}
							break;
						default:
							break;
					}

					Item* pItem;

					if ( isLairItem )
					{
						const MonsterInfo* pMonsterInfo = g_pMonsterInfoManager->getMonsterInfo(masterType);
						TreasureList *pTreasureList = NULL;

						if (pPC->isSlayer())
							pTreasureList = pMonsterInfo->getSlayerTreasureList();
						else if ( pPC->isVampire() )
							pTreasureList = pMonsterInfo->getVampireTreasureList();
						else if ( pPC->isOusters() )
							pTreasureList = pMonsterInfo->getOustersTreasureList();

						const list<Treasure*>& treasures = pTreasureList->getTreasures();

						list<Treasure*>::const_iterator itr = treasures.begin();

						ITEM_TEMPLATE it;

						for(; itr != treasures.end(); itr++)
						{
							Treasure* pTreasure = (*itr);

							it.ItemClass = Item::ITEM_CLASS_MAX;
							it.ItemType = 0;

							it.NextOptionRatio = 0;

							//cout << "TradeLairItem: BonusRatio = " << it.NextOptionRatio << endl;

							if ( pTreasure->getRandomItem(&it) )
							{
								pItem = g_pItemFactoryManager->createItem(it.ItemClass, it.ItemType, it.OptionType);
								Assert(pItem != NULL);
							}
						}

					}
					else
					{
						pItem = g_pItemFactoryManager->createItem( iClass, iType, oList );
					}

					GenderRestriction gender = GENDER_BOTH;
					switch( pPC->getSex() )
					{
						case MALE:
							gender = GENDER_MALE;
							break;
						case FEMALE:
							gender = GENDER_FEMALE;
							break;
						default:
							break;
					}

					setItemGender( pItem, gender );

					_TPOINT tp;

					if ( pItem != NULL && pPC->getInventory()->addItem( pItem, tp ) )
					{
						pPC->getZone()->registerObject( pItem );
						pItem->create( pPC->getName(), STORAGE_INVENTORY, 0, tp.x, tp.y );

						if ( isTimeLimit )
						{
							pPC->addTimeLimitItem( pItem, 604800 );
							pPC->sendTimeLimitItemInfo();
						}

						GCCreateItem gcCreateItem;
						makeGCCreateItem( &gcCreateItem, pItem, tp.x, tp.y );
						pPC->getPlayer()->sendPacket( &gcCreateItem );

						remainTraceLog( pItem, "GOD", pCreature->getName(), ITEM_LOG_CREATE, DETAIL_EVENTNPC);
					}
					else
					{
						if ( isUnique )
							pItem->setUnique();

						if ( isTimeLimit )
							pItem->setTimeLimitItem();

						pPC->setQuestItem( pItem );

						remainTraceLog( pItem, "GOD", pCreature->getName(), ITEM_LOG_CREATE, DETAIL_EVENTNPC);
					}

				}

				if ( pPC->getLottoQuestLevel() == 4 )
				{
					pPC->getQuestManager()->cancelQuest();
					GCNoticeEvent gcNE;
					gcNE.setCode( NOTICE_EVENT_START_QUEST_ENDING );
					pPC->getPlayer()->sendPacket( &gcNE );
				}
			}
			break;
		case TYPE_OVER_ENDING:
			{
				// 磷牢促. // PlayerCreature 俊辑绰 setHP 给 何甫淀
				//pPC->setHP(0);
				if ( pCreature != NULL )
				{
					if ( pCreature->isSlayer() )
					{
						Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
						pSlayer->setHP(0);
					}
					else if (pCreature->isVampire() )
					{
						Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
						pVampire->setHP(0);
					}
				}
			}
			break;
	}


#endif	// __GAME_SERVER__
		
	__END_DEBUG_EX __END_CATCH
}

