////////////////////////////////////////////////////////////////////////////////
// Project     : DARKEDEN
// Module      : Skill - Effect
// File Name   : EffectVigorDrop.h
// Writer      : 장홍창
// Date        : 2002.3.28
// Description :
//               Vigor Drop은 --storm류의 기술과 동일한 방식으로 구현되는
//               Slayer의 기술이다.
//               기술을 사용하게 되면, 기술 시전 지역을 중심으로 3x3의 영역에
//               EffectVigorDrop Effect가 붙게 된다. EffectVigorDrop Effect
//               는 독자적으로 데미지를 가하는 기술이 아니라.
//               해당 지역의 Creature에게 EffectVigorDropToCreature Effect를
//               붙이고 사라진다. EffectVigorDropToCreature는 VigorDrop의
//               전체 데미지의 1/3에 해당하는 Damage를 3번 연속으로 해당 
//               Creature에게 가하고 사라진다. 
//     
// History
//     DATE      WRITER         DESCRIPTION
// =========== =========== =====================================================
// 2002.3.28    장홍창      header file 작성
//
//
////////////////////////////////////////////////////////////////////////////////

#include "VigorDrop.h"
#include "EffectVigorDrop.h"

#include "GCSkillToTileOK1.h"
#include "GCSkillToTileOK2.h"
#include "GCSkillToTileOK3.h"
#include "GCSkillToTileOK4.h"
#include "GCSkillToTileOK5.h"
#include "GCSkillToTileOK6.h"
#include "GCAddEffect.h"
#include "GCAddEffectToTile.h"

//////////////////////////////////////////////////////////////////////////////
// 뱀파이어 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void VigorDrop::execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
    
{
    __BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "begin " << endl;

	// Slayer Object Assertion
	Assert(pSlayer != NULL);
	Assert(pSkillSlot != NULL);

    try
    {
		Zone* pZone = pSlayer->getZone();
		Assert(pZone != NULL);

		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
		//Assert(pTargetCreature != NULL);

		// NoSuch제거. by sigi. 2002.5.2
		if (pTargetCreature==NULL
			|| !canAttack( pSlayer, pTargetCreature )
			|| pTargetCreature->isNPC())
		{
			executeSkillFailException(pSlayer, getSkillType());
		    
			return;
		}

		execute(pSlayer, pTargetCreature->getX(), pTargetCreature->getY(), pSkillSlot, CEffectID);
    } 
	catch (Throwable & t) 
	{
		executeSkillFailException(pSlayer, getSkillType());
        //cout << t.toString() << endl;
    }

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;

    __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 뱀파이어 타일 핸들러
//  뱀파이어가 Vigor Drop Skill을 Tile에 사용했을때 사용하는 Handler
//////////////////////////////////////////////////////////////////////////////
void VigorDrop::execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "begin " << endl;

	try
	{
		Player* pPlayer = pSlayer->getPlayer();
		Zone* pZone = pSlayer->getZone();

		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		GCSkillToTileOK1 _GCSkillToTileOK1;
		GCSkillToTileOK2 _GCSkillToTileOK2;
		GCSkillToTileOK3 _GCSkillToTileOK3;
		GCSkillToTileOK4 _GCSkillToTileOK4;
		GCSkillToTileOK5 _GCSkillToTileOK5;
		GCSkillToTileOK6 _GCSkillToTileOK6;

		// Skillype을 가지고 
		//    SkillInfo
		//    SkillDomainInfo정보를 가져온다.
		//   SkillDomain정보는 기술이 성공했을 경우 해당 계열의 경험치를 올리기 위한 것이다.
		SkillType_t SkillType = pSkillSlot->getSkillType();
		SkillInfo*  pSkillInfo =  g_pSkillInfoManager->getSkillInfo(SkillType);
		SkillDomainType_t DomainType = pSkillInfo->getDomainType();

		ZoneCoord_t myX = pSlayer->getX();
		ZoneCoord_t myY = pSlayer->getY();

		int  RequiredMP = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck = hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck = verifyRunTime(pSkillSlot);
		bool bRangeCheck = verifyDistance(pSlayer, X, Y, pSkillInfo->getRange());
		bool bHitRoll = HitRoll::isSuccessMagic(pSlayer, pSkillInfo, pSkillSlot);

		bool bTileCheck = false;

		VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);

		if(rect.ptInRect(X, Y))
		{
			Tile& tile = pZone->getTile(X, Y);
			if (tile.canAddEffect()) bTileCheck = true;
		}


		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && bTileCheck)
		{
			decreaseMana(pSlayer, RequiredMP, _GCSkillToTileOK1);

			// calculate damage and duration time
			SkillInput input(pSlayer, pSkillSlot);
			SkillOutput output;
			computeOutput(input, output);

			Range_t Range = 3;

			// 기존에 같은 이펙트가 타일에 있다면 지우고 새로 설정한다.
			Tile& tile = pZone->getTile(X, Y);
			Effect* pOldEffect = tile.getEffect(Effect::EFFECT_CLASS_VIGOR_DROP);
			if(pOldEffect != NULL)
			{
				ObjectID_t effectID = pOldEffect->getObjectID();
				pZone->deleteEffect(effectID);
			}

			// 이펙트 오브젝트를 생성해서 타일에 붙인다. 
			//cout << "make EffectObject to Tile" << X << " " << Y << endl;
			EffectVigorDrop* pEffect = new EffectVigorDrop(pZone, X, Y);

            // 우선권 시스템을 위하여 이름과 파티 아이디를 넣는다.
			pEffect->setCasterName(pSlayer->getName());
			pEffect->setPartyID(pSlayer->getPartyID());

			pEffect->setDeadline(output.Duration);
			pEffect->setNextTime(0);
			pEffect->setTick(output.Tick);
			pEffect->setDamage(output.Damage);
			pEffect->setLevel(pSkillInfo->getLevel()/2);

			//
			ObjectRegistry& objectregister = pZone->getObjectRegistry();
			objectregister.registerObject(pEffect);

			//
			//
			//pZone->addEffect(pEffect);
			//tile.addEffect(pEffect);


			// 이펙트 범위내의 모든 Creature에게 effect를 붙여준다.
			// Slayer가 기술을 사용한 경우 같은 Slayer에게는
			// 해당하지 않는다.
			bool bEffected = false;
			bool bHit = false;
			Creature* pTargetCreature;


			list<Creature*> cList;
			cList.push_back(pSlayer);

			int oX, oY;

			for(oX = -2; oX <= 2; oX++)
			for(oY = -2; oY <= 2; oY++)
			{
				int tileX = X+oX;
				int tileY = Y+oY;
				if (!rect.ptInRect(tileX, tileY)) continue;

				Tile& tile = pZone->getTile(tileX, tileY);
		    	if (!tile.canAddEffect()) continue; 

				pTargetCreature = NULL;
				if(tile.hasCreature(Creature::MOVE_MODE_WALKING))
					pTargetCreature = tile.getCreature(Creature::MOVE_MODE_WALKING);

				if(pTargetCreature != NULL)
				{
					if(pTargetCreature->isVampire())
					{
						if(pEffect->affectCreature(pTargetCreature, false) == true)
						{
							//cout << "VigorDrop to Slayer Success" << endl;
							Player* pTargetPlayer = pTargetCreature->getPlayer();
							bEffected = true;

							// 경험치 상승을 위해서 Hit/Don'tHie를 기록한다.
							bHit = true;

							bool bCanSee = canSee(pTargetCreature, pSlayer);

							_GCSkillToTileOK1.addCListElement(pTargetCreature->getObjectID());
							_GCSkillToTileOK4.addCListElement(pTargetCreature->getObjectID());
							_GCSkillToTileOK5.addCListElement(pTargetCreature->getObjectID());

							cList.push_back(pTargetCreature);

							if (bCanSee)
							{
								// 공격을 당한 사람에게 
								_GCSkillToTileOK2.setObjectID(pSlayer->getObjectID());
								_GCSkillToTileOK2.setSkillType(SkillType);
								_GCSkillToTileOK2.setX(X);
								_GCSkillToTileOK2.setY(Y);
								_GCSkillToTileOK2.setDuration(output.Duration);
								_GCSkillToTileOK2.setRange(Range);
								pTargetPlayer->sendPacket(&_GCSkillToTileOK2);
							}
						}
						else
						{
							//cout << "VigorDrop to creature fail" << endl;
						}
					}
					else if(pTargetCreature->isMonster())
					{
						if(pEffect->affectCreature(pTargetCreature, false) == true)
						{
							//cout << "VigorDrop to Monster Success" << endl;
							bHit = true;
							Monster* pMonster = dynamic_cast<Monster*>(pTargetCreature);
							pMonster->addEnemy(pSlayer);

							// 마지막 때린 애가 슬레이어라고 설정한다. by sigi. 2002.6.21
							pMonster->setLastHitCreatureClass(Creature::CREATURE_CLASS_SLAYER);
						}
					}
				} // if(pTargetCreature!= NULL)
			}

			if( bHit ) {
				// 기술이 타일내에서 한번이라도 성공했을때에는 경험치를 받는다. 
				// 광역기술내에서 여러 Creature한테 데미지를 준 경우에는 어떻게 하는가?
				// 1. 한 Creature에게 준 데미지를 Point로 계산한다.
				// 2. 여러 Creature에게 준 데미지의 합을 Point로 계산한다.
				shareAttrExp(pSlayer, output.Damage, 1, 1, 8, _GCSkillToTileOK1);
				increaseDomainExp(pSlayer, DomainType, pSkillInfo->getPoint(), _GCSkillToTileOK1);
				increaseSkillExp(pSlayer, DomainType,  pSkillSlot, pSkillInfo, _GCSkillToTileOK1);
			}

			// 기술을 사용한 사람들에게
			_GCSkillToTileOK1.setSkillType(SkillType);
			_GCSkillToTileOK1.setCEffectID(CEffectID);
			_GCSkillToTileOK1.setX(X);
			_GCSkillToTileOK1.setY(Y);
			_GCSkillToTileOK1.setDuration(output.Duration);
			_GCSkillToTileOK1.setRange(Range);
		
			// 기술을 쓴 사람만 볼 수 있는 사람들에게
			_GCSkillToTileOK3.setSkillType(SkillType);
			_GCSkillToTileOK3.setX(X);
			_GCSkillToTileOK3.setY(Y);
			//_GCSkillToTileOK3.setDuration(output.Duration);
			//_GCSkillToTileOK3.setRange(Range);

			// 기술을 당한 사람만 볼 수 있는 사람들에게
			_GCSkillToTileOK4.setSkillType(SkillType);
			_GCSkillToTileOK4.setX(X);
			_GCSkillToTileOK4.setY(Y);
			_GCSkillToTileOK4.setDuration(output.Duration);
			_GCSkillToTileOK4.setRange(Range);

			//기술을 쓴 사람과 당한 사람을 모두 볼 수 있는 사람들에게
			_GCSkillToTileOK5.setObjectID(pSlayer->getObjectID());
			_GCSkillToTileOK5.setSkillType(SkillType);
			_GCSkillToTileOK5.setX(X);
			_GCSkillToTileOK5.setY(Y);
			_GCSkillToTileOK5.setDuration(output.Duration);
			_GCSkillToTileOK5.setRange(Range);
	
			// 기술을 사용한 사람에게 packet 전달
			pPlayer->sendPacket(&_GCSkillToTileOK1);

			// 기술을 쓸 사람과 당한 사람을 모두 볼 수 있는 사람들에게 broadcasing
			// broadcasting후 5번OK를 받은 사람을 기록한다.
			// 여기에 기록된 사람은 차후 broadcasting에서 제외된다.
			cList = pZone->broadcastSkillPacket(myX, myY, X, Y, &_GCSkillToTileOK5, cList);
			
			// 기술을 쓴 사람을 볼 수 있는 사람들에게 broadcasting
			pZone->broadcastPacket(myX, myY, &_GCSkillToTileOK3, cList);

			// 기술을 당한 사람을 볼 수 있는 사람들에게 broadcasting
			pZone->broadcastPacket(X, Y, &_GCSkillToTileOK4, cList);

			// 기술 delay setting
			pSkillSlot->setRunTime(output.Delay);
		}
		else
		{
			executeSkillFailNormal(pSlayer, getSkillType(), NULL);
		}
	}
	catch(Throwable& t)
	{
		executeSkillFailException(pSlayer, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 몬스터 타일 핸들러
//////////////////////////////////////////////////////////////////////////////
void VigorDrop::execute(Monster* pMonster, ZoneCoord_t X, ZoneCoord_t Y)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "begin " << endl;

	try
	{
		Zone* pZone = pMonster->getZone();

		Assert(pZone != NULL);

		GCSkillToTileOK1 _GCSkillToTileOK1;
		GCSkillToTileOK2 _GCSkillToTileOK2;
		GCSkillToTileOK3 _GCSkillToTileOK3;
		GCSkillToTileOK4 _GCSkillToTileOK4;
		GCSkillToTileOK5 _GCSkillToTileOK5;
		GCSkillToTileOK6 _GCSkillToTileOK6;

		SkillType_t SkillType = SKILL_VIGOR_DROP;
		SkillInfo*  pSkillInfo =  g_pSkillInfoManager->getSkillInfo(SkillType);

		ZoneCoord_t myX = pMonster->getX();
		ZoneCoord_t myY = pMonster->getY();

		bool bRangeCheck = verifyDistance(pMonster, X, Y, pSkillInfo->getRange());
		bool bHitRoll = HitRoll::isSuccessMagic(pMonster, pSkillInfo);

		bool bTileCheck = false;

		VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);

		if(rect.ptInRect(X, Y))
		{
			Tile& tile = pZone->getTile(X, Y);
			if (tile.canAddEffect()) bTileCheck = true;
		}

		if (bRangeCheck && bHitRoll && bTileCheck)
		{
			// calculate damage and duration time
			SkillInput input(pMonster);
			SkillOutput output;
			computeOutput(input, output);

			Range_t Range = 3;

			// 기존에 같은 이펙트가 타일에 있다면 지우고 새로 설정한다.
			Tile& tile = pZone->getTile(X, Y);
			Effect* pOldEffect = tile.getEffect(Effect::EFFECT_CLASS_VIGOR_DROP);
			if(pOldEffect != NULL)
			{
				ObjectID_t effectID = pOldEffect->getObjectID();
				pZone->deleteEffect(effectID);
			}

			// 이펙트 오브젝트를 생성해서 타일에 붙인다. 
			EffectVigorDrop* pEffect = new EffectVigorDrop(pZone, X, Y);
			pEffect->setDeadline(output.Duration);
			pEffect->setNextTime(0);
			pEffect->setTick(output.Tick);
			pEffect->setDamage(output.Damage);
			pEffect->setLevel(pSkillInfo->getLevel()/2);

			//
			ObjectRegistry& objectregister = pZone->getObjectRegistry();
			objectregister.registerObject(pEffect);

			//
			//
			pZone->addEffect(pEffect);
			tile.addEffect(pEffect);


			// 이펙트 범위내의 모든 Creature에게 effect를 붙여준다.
			// Slayer가 기술을 사용한 경우 같은 Slayer에게는
			// 해당하지 않는다.
			bool bEffected = false;
			Creature* pTargetCreature;


			list<Creature*> cList;
			cList.push_back(pMonster);

			int oX, oY;

			for(oX = -2; oX <= 2; oX++)
			for(oY = -2; oY <= 2; oY++)
			{
				int tileX = X+oX;
				int tileY = Y+oY;

				if(!rect.ptInRect(tileX, tileY)) continue;

				Tile& tile = pZone->getTile(tileX, tileY);

				if(!tile.canAddEffect()) continue;

				pTargetCreature = NULL;
				if(tile.hasCreature(Creature::MOVE_MODE_WALKING))
					pTargetCreature = tile.getCreature(Creature::MOVE_MODE_WALKING);

				if(pTargetCreature != NULL)
				{
					if(pTargetCreature->isPC())
					{
						if(pEffect->affectCreature(pTargetCreature, false) == true)
						{
							Player* pTargetPlayer = pTargetCreature->getPlayer();
							bEffected = true;

							bool bCanSee = canSee(pTargetCreature, pMonster);

							_GCSkillToTileOK1.addCListElement(pTargetCreature->getObjectID());
							_GCSkillToTileOK4.addCListElement(pTargetCreature->getObjectID());
							_GCSkillToTileOK5.addCListElement(pTargetCreature->getObjectID());

							cList.push_back(pTargetCreature);

							if (bCanSee)
							{
								// 공격을 당한 사람에게 
								_GCSkillToTileOK2.setObjectID(pMonster->getObjectID());
								_GCSkillToTileOK2.setSkillType(SkillType);
								_GCSkillToTileOK2.setX(X);
								_GCSkillToTileOK2.setY(Y);
								_GCSkillToTileOK2.setDuration(output.Duration);
								_GCSkillToTileOK2.setRange(Range);
								pTargetPlayer->sendPacket(&_GCSkillToTileOK2);
							}
						}
					}
				} // if(pTargetCreature!= NULL)
			}

			// 기술을 쓴 사람만 볼 수 있는 사람들에게
			_GCSkillToTileOK3.setSkillType(SkillType);
			_GCSkillToTileOK3.setX(myX);
			_GCSkillToTileOK3.setY(myY);
			//_GCSkillToTileOK3.setDuration(output.Duration);
			//_GCSkillToTileOK3.setRange(Range);

			// 기술을 당한 사람만 볼 수 있는 사람들에게
			_GCSkillToTileOK4.setSkillType(SkillType);
			_GCSkillToTileOK4.setX(X);
			_GCSkillToTileOK4.setY(Y);
			_GCSkillToTileOK4.setDuration(output.Duration);
			_GCSkillToTileOK4.setRange(Range);

			//기술을 쓴 사람과 당한 사람을 모두 볼 수 있는 사람들에게
			_GCSkillToTileOK5.setObjectID(pMonster->getObjectID());
			_GCSkillToTileOK5.setSkillType(SkillType);
			_GCSkillToTileOK5.setX(X);
			_GCSkillToTileOK5.setY(Y);
			_GCSkillToTileOK5.setDuration(output.Duration);
			_GCSkillToTileOK5.setRange(Range);
	
			// 기술을 쓸 사람과 당한 사람을 모두 볼 수 있는 사람들에게 broadcasing
			cList = pZone->broadcastSkillPacket(myX, myY, X, Y, &_GCSkillToTileOK5, cList);
			
			// 기술을 쓴 사람을 볼 수 있는 사람들에게 broadcasting
			pZone->broadcastPacket(myX, myY, &_GCSkillToTileOK3, cList);

			// 기술을 당한 사람을 볼 수 있는 사람들에게 broadcasting
			pZone->broadcastPacket(X, Y, &_GCSkillToTileOK4, cList);

		}
		else
		{
			executeSkillFailNormal(pMonster, getSkillType(), NULL);
		}
	}
	catch(Throwable& t)
	{
		executeSkillFailException(pMonster, getSkillType());
	}


	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;

	__END_CATCH
}
VigorDrop g_VigorDrop;
