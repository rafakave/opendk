//----------------------------------------------------------------------
// 
// Filename    : CLCreatePC.h 
// Written By  : Reiot
// Description : 
// 
//----------------------------------------------------------------------

#ifndef __CL_CREATE_PC_H__
#define __CL_CREATE_PC_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include <bitset>

//----------------------------------------------------------------------
//
// class CLCreatePC;
//
// 슬레이어 캐릭터를 새로 만들 경우, 이 패킷에 정보를 담아서 서버로 전송한다.
//
//----------------------------------------------------------------------

class CLCreatePC : public Packet {

public:

    enum {
        SLAYER_BIT_SEX ,
		SLAYER_BIT_HAIRSTYLE ,
		SLAYER_BIT_HAIRSTYLE2 ,
		SLAYER_BIT_MAX
    };

	enum {
		SLAYER_COLOR_HAIR ,
		SLAYER_COLOR_SKIN ,
		SLAYER_COLOR_SHIRT ,
		SLAYER_COLOR_SHIRT2 ,
		SLAYER_COLOR_JEANS ,
		SLAYER_COLOR_JEANS2 ,
		SLAYER_COLOR_MAX
	};


public:
	CLCreatePC() {};
    virtual ~CLCreatePC() {};
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_CL_CREATE_PC; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static CLCreatePCPacketSize 를 정의, 리턴하라.
	PacketSize_t getPacketSize() const  
	{ 
		return szBYTE + m_Name.size() 	// 이름
			+ szSlot					// 슬랏
			+ szBYTE					// 슬레이어 플래그(3 bit)
			+ szAttr* 3
			+ szColor* SLAYER_COLOR_MAX ; // 색깔 정보
	}

	// get packet's name
	string getPacketName() const  { return "CLCreatePC"; }
	
	// get packet's debug string
	string toString() const ;

public:

	// get/set name
	string getName() const  { return m_Name; }
	void setName(string name)  { m_Name = name; }

	// get/set slot
	Slot getSlot() const  { return m_Slot; }
	void setSlot(Slot slot)  { m_Slot = slot; }

	// get/set sex
    Sex getSex() const  { return m_BitSet.test(SLAYER_BIT_SEX)?MALE:FEMALE; }
    void setSex(Sex sex)  { m_BitSet.set(SLAYER_BIT_SEX,(sex==MALE?true:false)); }

	// get/set hair style
	HairStyle getHairStyle() const  { return HairStyle((m_BitSet.to_ulong() >> 1) & 3); }
	void setHairStyle(HairStyle hairStyle)  { m_BitSet |= bitset<SLAYER_BIT_MAX>(hairStyle << 1); }

	// get/set race. by sigi. 2002.10.31
	//bool isSlayer() const  { return ((m_BitSet.to_ulong() >> 3) & 1)==0; }
	//void setSlayer(bool bSlayer=true)  { m_BitSet |= bitset<SLAYER_BIT_MAX>((int)(bSlayer==false) << 3); }

	// get/set hair color
	Color_t getHairColor() const  { return m_Colors[ SLAYER_COLOR_HAIR ]; }
	void setHairColor(Color_t hairColor)  { m_Colors[ SLAYER_COLOR_HAIR ] = hairColor; }

	// get/set skin color
	Color_t getSkinColor() const  { return m_Colors[ SLAYER_COLOR_SKIN ]; }
	void setSkinColor(Color_t skinColor)  { m_Colors[ SLAYER_COLOR_SKIN ] = skinColor; }

	// get/set shirt color
	Color_t getShirtColor(ColorType colorType = MAIN_COLOR) const  { return m_Colors[ SLAYER_COLOR_SHIRT +(uint)colorType ]; }
	void setShirtColor(Color_t shirtColor, ColorType colorType = MAIN_COLOR)  { m_Colors[ SLAYER_COLOR_SHIRT +(uint)colorType ] = shirtColor; }

	// get/set jeans color
	Color_t getJeansColor(ColorType colorType = MAIN_COLOR) const  { return m_Colors[ SLAYER_COLOR_JEANS +(uint)colorType ]; }
	void setJeansColor(Color_t jeansColor, ColorType colorType = MAIN_COLOR)  { m_Colors[ SLAYER_COLOR_JEANS +(uint)colorType ] = jeansColor; }

	// get/set STR
	Attr_t getSTR() const  { return m_STR; }
	void setSTR(Attr_t str)  { m_STR = str; }
	// get/set DEX
	Attr_t getDEX() const  { return m_DEX; }
	void setDEX(Attr_t dex)  { m_DEX = dex; }
	// get/set INT
	Attr_t getINT() const  { return m_INT; }
	void setINT(Attr_t inte)  { m_INT = inte; }

	// get/set Race
	Race_t getRace() const  { return m_Race; }
	void setRace(Race_t race )  { m_Race = race; }


private :

    // PC의 이름
    string m_Name;

	// 슬랏
	Slot m_Slot;

	// 슬레이어 플래그 
	bitset<SLAYER_BIT_MAX> m_BitSet; 

	// 슬레이어 색깔 정보
	Color_t m_Colors[SLAYER_COLOR_MAX ];

	// STR, DEX, INTE
	Attr_t m_STR;
	Attr_t m_DEX;
	Attr_t m_INT;

	// 종족
	Race_t m_Race;

};


//////////////////////////////////////////////////////////////////////
//
// class CLCreatePCFactory;
//
// Factory for CLCreatePC
//
//////////////////////////////////////////////////////////////////////

class CLCreatePCFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket()  { return new CLCreatePC(); }

	// get packet name
	string getPacketName() const  { return "CLCreatePC"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_CL_CREATE_PC; }

	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static CLCreatePCPacketSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() const 
	{ 
		return szBYTE + 20 								// 이름
			+ szSlot									// 슬랏
			+ szBYTE									// 슬레이어 플래그(3 bit)
			+ szAttr* 3
			+ szColor* CLCreatePC::SLAYER_COLOR_MAX 	// 색깔 정보
			+ szRace;									// 종족
	}

};


//////////////////////////////////////////////////////////////////////
//
// class CLCreatePCHandler;
//
//////////////////////////////////////////////////////////////////////

class CLCreatePCHandler {

public:

	// execute packet's handler
	static void execute(CLCreatePC* pPacket, Player* pPlayer) ;

};

#endif
