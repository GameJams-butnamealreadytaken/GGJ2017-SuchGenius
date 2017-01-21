#include "Plugin.h"

#include "ShSDK/ShSDK.h"

const CShIdentifier plugin_identifier("PluginGGJ2017");
const b2Vec2 gravity(0.0f, -9.8f);
const int ratio_sh_b2 = 100;

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

	//
	// Dummy AABB2
	CShArray<ShDummyAABB2 *> dummyAABB2;
	ShDummyAABB2::GetDummyAABB2Array(levelIdentifier, dummyAABB2);
	int iObjectCount = dummyAABB2.GetCount();

	for (int nDummy = 0; nDummy < iObjectCount; ++nDummy)
	{
		ShObject * pObject = dummyAABB2[nDummy];
		int iDataSetCount = ShObject::GetDataSetCount(pObject);
		for (int i = 0; i < iDataSetCount; ++i)
		{
			ShDataSet * pDataSet = ShObject::GetDataSet(pObject, i);
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
	m_pWorld->Step(dt, 8, 3);
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
				bodyDef.type = b2_kinematicBody;
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

		b2Vec2 * aB2Point = (b2Vec2*)malloc(sizeof(b2Vec2) * 4);
		aB2Point[0] = Convert_sh_b2(vPoint1) - pBody->GetPosition();
		aB2Point[1] = Convert_sh_b2(vPoint2) - pBody->GetPosition();
		aB2Point[2] = Convert_sh_b2(vPoint3) - pBody->GetPosition();
		aB2Point[3] = Convert_sh_b2(vPoint4) - pBody->GetPosition();

		pPolygonShape->Set(aB2Point, 4);
		free(aB2Point);
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