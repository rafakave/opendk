#ifndef __GUILD_UNION_H__
#define __GUILD_UNION_H__

#include "Types.h"
#include "Exception.h"
#include <list>
#include <unordered_map>
#include "GCUnionOfferList.h"

#include "Mutex.h"

class GuildUnionManager;
class GuildUnion
{
public:
	GuildUnion(GuildID_t master) : m_MasterGuildID(master) { }
	~GuildUnion();
		
	GuildID_t	getMasterGuildID() const { return m_MasterGuildID; }

	uint		getUnionID() const { return m_UnionID; }
	void		setUnionID( uint ID ) { m_UnionID = ID; }

	bool		hasGuild( GuildID_t gID ) const;
	bool		addGuild( GuildID_t gID ) ;
	bool		removeGuild( GuildID_t gId ) ;

	void		create() ;
	void		destroy() ;

	list<GuildID_t>	getGuildList()	const	{ return m_Guilds; }
	
protected:
	list<GuildID_t>::const_iterator findGuildItr( GuildID_t gID ) const {
    list<GuildID_t>::const_iterator itr = m_Guilds.begin();
    for (;itr != m_Guilds.end(); itr++) {
      if (*itr == gID) {
        break;
      }
    }
    return itr;
  }
	list<GuildID_t>::iterator findGuildItr( GuildID_t gID ) {
    // return find( m_Guilds.begin(), m_Guilds.end(), gID );
    list<GuildID_t>::iterator itr = m_Guilds.begin();
    for (;itr != m_Guilds.end(); itr++) {
      if (*itr == gID) {
        break;
      }
    }
    return itr;
  }

private:
	uint		m_UnionID;
	GuildID_t	m_MasterGuildID;
	list<GuildID_t>	m_Guilds;

	friend class GuildUnionManager;
};

class GuildUnionManager
{
public:
	GuildUnionManager();
	~GuildUnionManager();

	void	reload()	;
	void	load() ;
	void	addGuildUnion( GuildUnion* pUnion );
	GuildUnion*	getGuildUnion( GuildID_t gID ) { return m_GuildUnionMap[gID]; }
	GuildUnion* getGuildUnionByUnionID( uint uID ) { return m_UnionIDMap[uID]; }

	bool	addGuild( uint uID, GuildID_t gID ) ;
	bool 	removeMasterGuild(GuildID_t gID) ;
	bool	removeGuild( uint uID, GuildID_t gID ) ;

	void	sendRefreshCommand()	;
	void	sendModifyUnionInfo(uint gID)	;
	
	static GuildUnionManager& Instance()
	{
		static GuildUnionManager theInstance;
		return theInstance;
	}

private:
	list<GuildUnion*>					m_GuildUnionList;
	unordered_map<GuildID_t, GuildUnion*>	m_GuildUnionMap;
	unordered_map<uint, GuildUnion*>			m_UnionIDMap;


	// Mutex
	mutable Mutex m_Mutex;
};

class GuildUnionOffer
{
public:
	enum OfferType
	{
		JOIN,
		QUIT
	};
	BYTE	m_Type;
	GuildID_t	m_GuildID;
	string		m_MasterID;
	string		m_GuildName;
	string		m_MasterName;

};

class GuildUnionOfferManager
{
public:
	enum ErrorType
	{
		OK = 0,
		ALREADY_IN_UNION,
		ALREADY_OFFER_SOMETHING,
		TARGET_IS_NOT_MASTER,	// ???????? ???????? ????????;;
		NOT_IN_UNION,
		MASTER_CANNOT_QUIT,		// ?????? ?????? ?????? ?????? ????????(?????????? ???????? ????-????????)
		NO_TARGET_UNION,
		NOT_YOUR_UNION,
		SOURCE_IS_NOT_MASTER,	// ?????? ?????? ???????? ??????
		YOU_HAVE_PENALTY,		// ?????? ?????? ?????? ????. ?????? ?? ????
		NOT_ENOUGH_SLOT,			// OfferJoin??...?????? ?? ???? Slot?? ???? ????.
		TOO_MANY_MEMBER				// ?????? 50?? ???????? ?????? ?? ????.
			
		
	};
	uint	offerJoin( GuildID_t gID, GuildID_t MasterGID ) ;	// ???????? ????
	uint	offerQuit( GuildID_t gID ) ;						// ???????? ????

	uint	acceptJoin( GuildID_t gID ) ;						// ???????? ????
	uint	acceptQuit( GuildID_t gID ) ;						// ???????? ????

	uint	denyJoin( GuildID_t gID ) ;							// ???????? ????
	uint	denyQuit( GuildID_t gID ) ;							// ???????? ????

	void	clearOffer( GuildID_t gID ) ;	
	bool	hasOffer( GuildID_t gID ) ;

	bool	makeOfferList( uint uID, GCUnionOfferList& offerList ) ;	// ????????

	static GuildUnionOfferManager& Instance()
	{
		static GuildUnionOfferManager theInstance;
		return theInstance;
	}
};

#endif
