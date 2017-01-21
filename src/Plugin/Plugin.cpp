#include "Plugin.h"

#include "ShSDK/ShSDK.h"

const CShIdentifier plugin_identifier("PluginGGJ2017");
const b2Vec2 gravity(0.0f, -9.8f);
const int ratio_sh_b2 = 100;

#define DURATION 0.3f
#define WAVE_SIZE (256.0f*0.5f) // size of the sprite
#define MAX_DISTANCE (WAVE_SIZE)

/**
 * @brief Constructor
 */
PluginGGJ2017::PluginGGJ2017(void) : CShPlugin(plugin_identifier)
{
	// ...
}

/**
 * @brief Destructor
 */
PluginGGJ2017::~PluginGGJ2017(void)
{
	// ...
}

/**
 * @brief OnPlayStart
 * @param levelIdentifier
 */
void PluginGGJ2017::OnPlayStart(const CShIdentifier & levelIdentifier)
{
	m_pWorld = new b2World(gravity);

	m_levelIdentifier = levelIdentifier;

	//
	// Load and parse all DummyAABB2 datasets
	CShArray<ShDummyAABB2 *> dummyAABB2;
	ShDummyAABB2::GetDummyAABB2Array(levelIdentifier, dummyAABB2);
	int nDummyCount = dummyAABB2.GetCount();

	for (int i = 0; i < nDummyCount; ++i)
	{
		ShObject * pObject = dummyAABB2[i];
		int iDataSetCount = ShObject::GetDataSetCount(pObject);
		for (int j = 0; j < iDataSetCount; ++j)
		{
			ShDataSet * pDataSet = ShObject::GetDataSet(pObject, j);
			DatasetParser(pObject, pDataSet);
		}
	}
}

/**
 * @brief OnPlayStop
 * @param levelIdentifier
 */
void PluginGGJ2017::OnPlayStop(const CShIdentifier & levelIdentifier)
{
	m_aBodyList.Empty();
	SH_SAFE_DELETE(m_pWorld);
}

/**
 * @brief OnPreUpdate
 */
void PluginGGJ2017::OnPreUpdate(void)
{
	// ...
}

/**
* @brief OnPostUpdate
* @param dt
*/
void PluginGGJ2017::OnPostUpdate(float dt)
{
	unsigned int iWaveCount = m_aShockWave.GetCount();

	for (int iWave = 0; iWave < iWaveCount; ++iWave)
	{
		ShockWave & wave = m_aShockWave[iWave];

		wave.time += dt;

		if (wave.time < DURATION)
		{
			float scale = (wave.time/DURATION);
			float alpha = 1.0f - (wave.time/DURATION);

			ShEntity2::SetScale(wave.pEntity, CShVector3(scale, scale, 1.0f));
			ShEntity2::SetAlpha(wave.pEntity, alpha);

			float radius_b2 = (WAVE_SIZE * scale) / ratio_sh_b2;

			b2Vec2 pos_b2 = Convert_sh_b2(wave.initialPosition);

			unsigned int iBodyCount = m_aBodyList.GetCount();

			for (auto iBody = 0; iBody < iBodyCount; ++iBody)
			{
				const b2Vec2 & pos = m_aBodyList[iBody]->GetPosition();

				b2Vec2 PointerToObject = pos - pos_b2;
				const float distance = PointerToObject.Normalize();

				if (distance < radius_b2)
				{
					b2Vec2 impulse(PointerToObject.x * (distance/(MAX_DISTANCE/ratio_sh_b2)) * 5.0f, PointerToObject.y * (distance/(MAX_DISTANCE/ratio_sh_b2)) * 5.0f);
					m_aBodyList[iBody]->ApplyLinearImpulseToCenter(impulse, true);
				}
			}
		}
		else
		{
			ShEntity2::SetShow(wave.pEntity, false); // TODO : remove it + destroy entity
		}
	}

	m_pWorld->Step(dt, 8, 3);

	UpdateShineObjects();
}

/**
 * @brief PluginGGJ2017::OnTouchDown
 * @param iTouch
 * @param positionX
 * @param positionY
 */
void PluginGGJ2017::OnTouchDown(int iTouch, float positionX, float positionY)
{
	// ...
}

/**
 * @brief PluginGGJ2017::OnTouchUp
 * @param iTouch
 * @param positionX
 * @param positionY
 */
void PluginGGJ2017::OnTouchUp(int iTouch, float positionX, float positionY)
{
	ShCamera * pCamera = ShCamera::GetCamera2D();

	CShVector2 windowPos(ShDisplay::GetWidth()*0.5f+positionX, ShDisplay::GetHeight()*0.5f-positionY);

	CShRay3 ray = ShCamera::Unproject(pCamera, windowPos);

	CShVector2 pos(ray.GetOrigin().m_x, ray.GetOrigin().m_y);

	ShockWave wave;
	wave.pEntity = ShEntity2::Create(m_levelIdentifier, GID(NULL), CShIdentifier("layer_default"), CShIdentifier("ggj17"), CShIdentifier("shockwave"), CShVector3(pos.m_x, pos.m_y, 10.0f), CShEulerAngles(0.0f, 0.0f, 0.0f), CShVector3(0.0f, 0.0f, 1.0f));
	wave.initialPosition = pos;
	wave.time = 0.0f;

	m_aShockWave.Add(wave);
}

/**
 * @brief PluginGGJ2017::OnTouchMove
 * @param iTouch
 * @param positionX
 * @param positionY
 */
void PluginGGJ2017::OnTouchMove(int iTouch, float positionX, float positionY)
{
	// ...
}

/**
* @brief PluginGGJ2017::DatasetParser
* @param pDataSet
*/
void PluginGGJ2017::DatasetParser(ShObject * pObject, ShDataSet * pDataSet)
{
	b2BodyDef bodyDef;
	b2FixtureDef bodyFixture;

	ShObject * pAttachedObject = shNULL;

	int iDataCount = ShDataSet::GetDataCount(pDataSet);
	for (int nData = 0; nData < iDataCount; ++nData)
	{
		//
		// Body
		const CShIdentifier & idDataIdentifier = ShDataSet::GetDataIdentifier(pDataSet, nData);
		if (CShIdentifier("AttachedObject") == idDataIdentifier)
		{
			ShDataSet::GetDataValue(pDataSet, nData, &pAttachedObject);
			bodyDef.userData = pAttachedObject;
		}
		else if (CShIdentifier("allowSleep") == idDataIdentifier)
		{
			ShDataSet::GetDataValue(pDataSet, nData, bodyDef.allowSleep);
		}
		else if (CShIdentifier("awake") == idDataIdentifier)
		{
			ShDataSet::GetDataValue(pDataSet, nData, bodyDef.awake);
		}
		else if (CShIdentifier("fixedRotation") == idDataIdentifier)
		{
			ShDataSet::GetDataValue(pDataSet, nData, bodyDef.fixedRotation);
		}
		else if (CShIdentifier("bullet") == idDataIdentifier)
		{
			ShDataSet::GetDataValue(pDataSet, nData, bodyDef.bullet);
		}
		else if (CShIdentifier("active") == idDataIdentifier)
		{
			ShDataSet::GetDataValue(pDataSet, nData, bodyDef.active);
		}
		else if (CShIdentifier("isStatic") == idDataIdentifier)
		{
			bool isStatic = false;
			ShDataSet::GetDataValue(pDataSet, nData, isStatic);

			if (isStatic)
			{
				bodyDef.type = b2_staticBody;
			}
			else
			{
				bodyDef.type = b2_dynamicBody;
			}
		}

		//
		// Fixture
		if (CShIdentifier("friction") == idDataIdentifier)
		{
			float fFriction = 0.0f;
			ShDataSet::GetDataValue(pDataSet, nData, fFriction);
			bodyFixture.friction = fFriction;
		}
		else if (CShIdentifier("restitution") == idDataIdentifier)
		{
			float fRestitution = 0.0f;
			ShDataSet::GetDataValue(pDataSet, nData, fRestitution);
			bodyFixture.restitution = fRestitution;
		}
		else if (CShIdentifier("density") == idDataIdentifier)
		{
			float fDensity = 0.0f;
			ShDataSet::GetDataValue(pDataSet, nData, fDensity);
			bodyFixture.density = fDensity;
		}
		else if ((CShIdentifier("categoryBits") == idDataIdentifier))
		{
			int iCategories = 0;
			ShDataSet::GetDataValue(pDataSet, nData, iCategories);
			bodyFixture.filter.categoryBits = iCategories;
		}
		else if ((CShIdentifier("maskBits") == idDataIdentifier))
		{
			int iMask = 0;
			ShDataSet::GetDataValue(pDataSet, nData, iMask);
			bodyFixture.filter.maskBits = iMask;
		}
	}

	if (ShObject::GetType(pObject) != ShObject::e_type_unknown)
	{
		bodyDef.angle = ShObject::GetWorldRotation(pObject).m_z;
		bodyDef.position = Convert_sh_b2(ShObject::GetWorldPosition2(pObject));
	}

	b2Body * pBody = m_pWorld->CreateBody(&bodyDef);
	m_aBodyList.Add(pBody);

	b2Shape * pShape = GenerateBlockShape(pObject, pBody);
	SH_ASSERT(shNULL != pShape);

	if (shNULL != pShape)
	{
		bodyFixture.shape = pShape;

		b2Fixture * pFixture = pBody->CreateFixture(&bodyFixture);
	}
}

/**
* @brief PluginGGJ2017::DatasetParser
* @param pObject
* @param pBody
*/
b2Shape * PluginGGJ2017::GenerateBlockShape(ShObject * pObject, b2Body * pBody)
{
	if (ShObject::GetTypeIdentifier(pObject) != GID(dummy_aabb2))
	{
		SH_ASSERT_ALWAYS();
		return(shNULL);
	}

	b2PolygonShape * pPolygonShape = new b2PolygonShape();

	{
		ShDummyAABB2 * pDummy = (ShDummyAABB2*)pObject;
		CShVector3 scale = ShObject::GetWorldScale(pDummy);
		CShVector2 vDummyAABB2Translation = ShObject::GetWorldPosition2(pDummy);

		const CShAABB2 & aabb2 = ShDummyAABB2::GetAABB(pDummy);
		CShVector2 vPoint1(CShVector2(aabb2.m_min.m_x * scale.m_x, aabb2.m_min.m_y * scale.m_y) + vDummyAABB2Translation);
		CShVector2 vPoint2(CShVector2(aabb2.m_min.m_x * scale.m_x, aabb2.m_max.m_y * scale.m_y) + vDummyAABB2Translation);
		CShVector2 vPoint3(CShVector2(aabb2.m_max.m_x * scale.m_x, aabb2.m_max.m_y * scale.m_y) + vDummyAABB2Translation);
		CShVector2 vPoint4(CShVector2(aabb2.m_max.m_x * scale.m_x, aabb2.m_min.m_y * scale.m_y) + vDummyAABB2Translation);

		b2Vec2 aB2Point [4];
		aB2Point[0] = Convert_sh_b2(vPoint1) - pBody->GetPosition();
		aB2Point[1] = Convert_sh_b2(vPoint2) - pBody->GetPosition();
		aB2Point[2] = Convert_sh_b2(vPoint3) - pBody->GetPosition();
		aB2Point[3] = Convert_sh_b2(vPoint4) - pBody->GetPosition();

		pPolygonShape->Set(aB2Point, 4);
	}

	return(pPolygonShape);
}

/**
* @brief PluginGGJ2017::ConvertB2ToSh
* @param vec
*/
/*static*/ CShVector2 PluginGGJ2017::Convert_sh_b2(b2Vec2 vec)
{
	return CShVector2(vec.x, vec.y) * CShVector2(ratio_sh_b2, ratio_sh_b2);
}

/**
* @brief PluginGGJ2017::ConvertShToB2
* @param vec
*/
/*static*/ b2Vec2 PluginGGJ2017::Convert_sh_b2(CShVector2 vec)
{
	vec /= CShVector2(ratio_sh_b2, ratio_sh_b2);
	return b2Vec2(vec.m_x, vec.m_y);
}

/**
* @brief PluginGGJ2017::ConvertShToB2
* @param vec
*/
void PluginGGJ2017::UpdateShineObjects(void)
{
	int iBodyCount = m_aBodyList.GetCount();
	for (int nBody = 0; nBody < iBodyCount; ++nBody)
	{
		ShObject * pObject = (ShObject *)m_aBodyList[nBody]->GetUserData();

		if (shNULL != pObject)
		{
			//if (b2_staticBody != m_aBodyList[nBody]->GetType())
			{
				// only movable can be moved
				if (ShObject::IsMovable(pObject))
				{
					CShEulerAngles rotAngle(0.0f, 0.0f, m_aBodyList[nBody]->GetAngle());
					ShObject::SetWorldRotation(pObject, rotAngle);
					
					CShVector2 bodyPos = Convert_sh_b2(m_aBodyList[nBody]->GetPosition());
					ShObject::SetWorldPosition2(pObject, bodyPos);
				}
			}
		}
	}
}
