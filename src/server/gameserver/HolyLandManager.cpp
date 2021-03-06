#include "HolyLandManager.h"
#include "PCManager.h"
#include "PlayerCreature.h"
#include "ShrineInfoManager.h"
#include "Zone.h"

HolyLandManager::HolyLandManager()
	
{
	__BEGIN_TRY
	__END_CATCH
}

HolyLandManager::~HolyLandManager()
	
{
	__BEGIN_TRY

	clear();

	__END_CATCH
}

void HolyLandManager::addHolyLand( Zone* pZone )
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION( m_Mutex )

	HashMapZoneItor itr = m_HolyLands.find( pZone->getZoneID() );

	if ( itr != m_HolyLands.end() )
	{
		throw DuplicatedException();
	}

	m_HolyLands[ pZone->getZoneID() ] = pZone;

	__LEAVE_CRITICAL_SECTION( m_Mutex )
	
	__END_CATCH
}

void HolyLandManager::broadcast( Packet* pPacket ) const
	
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION( m_Mutex )

	HashMapZoneConstItor itr = m_HolyLands.begin();

	for( ; itr != m_HolyLands.end(); itr++ )
	{
		Zone* pZone = itr->second;
		Assert( pZone != NULL );

		pZone->broadcastPacket( pPacket );
	}

	__LEAVE_CRITICAL_SECTION( m_Mutex )

	__END_CATCH
}

/*void HolyLandManager::sendBloodBibleStatus() const 
	
{
	__BEGIN_TRY

	throw Error("Not Supported");

	__ENTER_CRITICAL_SECTION( m_Mutex )

	HashMapZoneConstItor itr = m_HolyLands.begin();

	for( ; itr != m_HolyLands.end(); itr++ )
	{
		Zone* pZone = itr->second;
		Assert( pZone != NULL );

		__ENTER_CRITICAL_SECTION((*pZone))

		const PCManager* pPCManager = pZone->getPCManager();
		const unordered_map< ObjectID_t, Creature* > & creatures = pPCManager->getCreatures();
		unordered_map< ObjectID_t, Creature* >::const_iterator itr;

		for (itr=creatures.begin(); itr!=creatures.end(); itr++)
		{
			Creature* pCreature = itr->second;
			Assert( pCreature->isPC() );

			PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
			g_pShrineInfoManager->sendBloodBibleStatus( pPC );
		}

		__LEAVE_CRITICAL_SECTION((*pZone))
	}

	__LEAVE_CRITICAL_SECTION( m_Mutex )

	__END_CATCH
}
*/
void HolyLandManager::fixTimeband( uint timeband )
	
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION( m_Mutex )

	HashMapZoneConstItor itr = m_HolyLands.begin();

	for( ; itr != m_HolyLands.end(); itr++ )
	{
		Zone* pZone = itr->second;
		Assert( pZone != NULL );

		pZone->stopTime();
		pZone->setTimeband( timeband );
		pZone->resetDarkLightInfo();
	}

	__LEAVE_CRITICAL_SECTION( m_Mutex )

	__END_CATCH
}

void HolyLandManager::resumeTimeband()
	
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION( m_Mutex )

	HashMapZoneConstItor itr = m_HolyLands.begin();

	for( ; itr != m_HolyLands.end(); itr++ )
	{
		Zone* pZone = itr->second;
		Assert( pZone != NULL );

		pZone->resumeTime();
		pZone->resetDarkLightInfo();
	}

	__LEAVE_CRITICAL_SECTION( m_Mutex )

	__END_CATCH
}


void    HolyLandManager::killAllMonsters() 
	
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION( m_Mutex )

	HashMapZoneConstItor itr = m_HolyLands.begin();

	for( ; itr != m_HolyLands.end(); itr++ )
	{
		Zone* pZone = itr->second;
		Assert( pZone != NULL );

		pZone->killAllMonsters();
	}

	__LEAVE_CRITICAL_SECTION( m_Mutex )


	__END_CATCH
}

void	HolyLandManager::remainRaceWarPlayers()
	
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION( m_Mutex )

	HashMapZoneConstItor itr = m_HolyLands.begin();

	for( ; itr != m_HolyLands.end(); itr++ )
	{
		Zone* pZone = itr->second;
		Assert( pZone != NULL );

		pZone->remainRaceWarPlayers();
	}

	__LEAVE_CRITICAL_SECTION( m_Mutex )

	__END_CATCH
}

void HolyLandManager::refreshHolyLandPlayers()
	
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION( m_Mutex )

	HashMapZoneConstItor itr = m_HolyLands.begin();

	for( ; itr != m_HolyLands.end(); itr++ )
	{
		Zone* pZone = itr->second;
		Assert( pZone != NULL );

		pZone->setRefreshHolyLandPlayer( true );
	}

	__LEAVE_CRITICAL_SECTION( m_Mutex )

	__END_CATCH
}

// global variable definition
HolyLandManager* g_pHolyLandManager = NULL;

