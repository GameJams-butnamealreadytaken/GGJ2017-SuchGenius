#include "Plugin.h"


const CShIdentifier plugin_identifier("PluginGGJ2017");
const b2Vec2 gravity(0.0f, -9.8f);
const int ratio_sh_b2 = 100;

#define DURATION 0.3f
#define WAVE_SIZE (256.0f*0.5f) // size of the sprite
#define MAX_DISTANCE (WAVE_SIZE)

/**
 * @brief Constructor
 */
PluginGGJ2017::PluginGGJ2017(void)
: CShPlugin(plugin_identifier)
, m_pWorld(shNULL)
, m_Box2DListener(shNULL)
, m_isOnSensor(0)
, m_arrivalTimer(0.0f)
, m_levelIdentifier(GID(NULL))
, m_iClicCount(0)
, m_isWon(false)
, m_PlayerInitPos()
, m_pPlayerBlock(shNULL)
, m_handleClick(false)
, m_mouseClick(-1)
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
* @brief Reset
*/
void PluginGGJ2017::Reset(void)
{
	int iBlockCount = m_aBlockList.GetCount();
	for (int i = 0; i < iBlockCount; ++i)
	{
		if (Block::PLAYER == m_aBlockList[i]->GetType())
		{
			b2Body * pBody = m_aBlockList[i]->GetBody();
			pBody->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
			pBody->SetAngularVelocity(0.0f);
			pBody->SetTransform(m_PlayerInitPos, 0.0f);
		}
	}

	m_isOnSensor = 0;
	m_iClicCount = 0;
	m_isWon = false;
}

/**
 * @brief OnPlayStart
 * @param levelIdentifier
 */
void PluginGGJ2017::OnPlayStart(const CShIdentifier & levelIdentifier)
{
	ShCamera * pCurrentCamera = ShCamera::GetCamera2D();
	const CShVector2 & viewport = ShCamera::GetViewport(pCurrentCamera);

	m_fTouchRatio = viewport.m_x / ShDisplay::GetWidth();

	m_pWorld = new b2World(gravity);

	m_Box2DListener = new Box2DListener();
	m_Box2DListener->Initialize(this);
	m_pWorld->SetContactListener(m_Box2DListener);

	m_levelIdentifier = levelIdentifier;

	//
	// Load and parse all DummyAABB2 datasets
	CShArray<ShDummyAABB2 *> aDummyAABB2;
	ShDummyAABB2::GetDummyAABB2Array(levelIdentifier, aDummyAABB2);
	int nDummyCount = aDummyAABB2.GetCount();

	for (int i = 0; i < nDummyCount; ++i)
	{
		ShObject * pObject = aDummyAABB2[i];
		int iDataSetCount = ShObject::GetDataSetCount(pObject);
		for (int j = 0; j < iDataSetCount; ++j)
#if 0 // Don't remove this, made by a baby
		*{
#endif // end baby code
		{
			ShDataSet * pDataSet = ShObject::GetDataSet(pObject, j);
			DatasetParser(pObject, pDataSet);
		}
	}

	//
	// Load and parse all Collision Shape
	CShArray<ShCollisionShape*> aCollisionShape;
	ShCollisionShape::GetCollisionShapeArray(levelIdentifier, aCollisionShape);
	int nShapeCount = aCollisionShape.GetCount();

	for (int i = 0; i < nShapeCount; ++i)
	{
		const CShVector2 pos = ShObject::GetWorldPosition2((ShObject*)aCollisionShape[i]);
		b2BodyDef bodyDef;
		bodyDef.position = Convert_sh_b2(pos);

		b2Body * pBody = m_pWorld->CreateBody(&bodyDef);
/*
		Block * pBlock = new Block();
		pBlock->Initialize(pBody, pAttachedSprite, type);
		m_aBlockList.Add(pBlock);

		pBody->SetUserData(pBlock);
*/

		b2Shape * pShape = GenerateStaticBlockShape(aCollisionShape[i], pBody);
		SH_ASSERT(shNULL != pShape);

		if (shNULL != pShape)
		{
			b2FixtureDef bodyFixture;
			bodyFixture.shape = pShape;

			b2Fixture * pFixture = pBody->CreateFixture(&bodyFixture);
		}
	}

	m_iClicCount = 0;
	m_arrivalTimer = 0.0f;
	m_isOnSensor = 0;
	m_isWon = false;
	m_handleClick = true;
	m_mouseClick = -1;
}

/**
 * @brief OnPlayStop
 * @param levelIdentifier
 */
void PluginGGJ2017::OnPlayStop(const CShIdentifier & levelIdentifier)
{
	m_iClicCount = 0;
	m_isWon = false;

	int iBlockCount = m_aBlockList.GetCount();
	for (int i = 0; i < iBlockCount; ++i)
	{
		m_aBlockList[i]->Release();
	}
	m_aBlockList.Empty();

	m_levelIdentifier = GID(NULL);

	SH_SAFE_DELETE(m_pWorld);

	SH_SAFE_DELETE(m_Box2DListener);
}

/**
 * @brief OnPreUpdate
 */
void PluginGGJ2017::OnPreUpdate(void)
{
	CapBlockVelocity(7.0f);
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

		if (wave.pEntity)
		{
			wave.time += dt;

			if (wave.time < DURATION)
			{
				float scale = (wave.time / DURATION);
				float alpha = 1.0f - (wave.time / DURATION);

				ShEntity2::SetScale(wave.pEntity, CShVector3(scale, scale, 1.0f));
				ShEntity2::SetAlpha(wave.pEntity, alpha);

				float radius_b2 = (WAVE_SIZE * scale) / ratio_sh_b2;

				b2Vec2 pos_b2 = Convert_sh_b2(wave.initialPosition);

				unsigned int iBlockCount = m_aBlockList.GetCount();

				for (auto iBody = 0; iBody < iBlockCount; ++iBody)
				{
					const b2Vec2 & pos = m_aBlockList[iBody]->GetBody()->GetPosition();

					b2Vec2 PointerToObject = pos - pos_b2;
					const float distance = PointerToObject.Normalize();

					if (distance < radius_b2)
					{
						b2Vec2 impulse(PointerToObject.x * (distance / (MAX_DISTANCE / ratio_sh_b2)) * 5.0f, PointerToObject.y * (distance / (MAX_DISTANCE / ratio_sh_b2)) * 5.0f);
						m_aBlockList[iBody]->GetBody()->ApplyLinearImpulseToCenter(impulse, true);
					}
				}
			}
			else
			{
				ShEntity2::Destroy(wave.pEntity);
				wave.pEntity = shNULL;
				// TODO : remove from array
			}
		}
	}

	m_pWorld->Step(dt, 8, 3);

	UpdateShineObjects();

	if (!m_isWon)
	{
		if (m_isOnSensor != 0)
		{
			m_arrivalTimer += dt;

			if (m_arrivalTimer >= 2.0f)
			{
				m_arrivalTimer = 0.0f;
				m_isWon = true;
				m_handleClick = false;
				m_mouseClick = -1;
			}
		}

		CheckForAutoRetry();
	}
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
	if (m_handleClick)
	{
		if (-1 == m_mouseClick)
		{
			m_mouseClick = 0;
			return;
		}

		if (GID(NULL) != m_levelIdentifier)
		{
			ShCamera * pCamera = ShCamera::GetCamera2D();

			CShVector2 windowPos(ShDisplay::GetWidth()*0.5f + positionX, ShDisplay::GetHeight()*0.5f - positionY);

			CShRay3 ray = ShCamera::Unproject(pCamera, windowPos * m_fTouchRatio);

			CShVector2 pos(ray.GetOrigin().m_x, ray.GetOrigin().m_y);

			ShockWave wave;
			wave.pEntity = ShEntity2::Create(m_levelIdentifier, GID(NULL), CShIdentifier("layer_default"), CShIdentifier("ggj17"), CShIdentifier("shockwave"), CShVector3(pos.m_x, pos.m_y, 10.0f), CShEulerAngles(0.0f, 0.0f, 0.0f), CShVector3(0.0f, 0.0f, 1.0f));
			wave.initialPosition = pos;
			wave.time = 0.0f;

			m_aShockWave.Add(wave);

			++m_iClicCount;
		}
	}
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
* @brief PluginGGJ2017::SetPlayerOnSensorA
* @param playerOnA
*/
void PluginGGJ2017::SetPlayerOnSensor(bool Inc)
{
	if (Inc)
	{
		++m_isOnSensor;
	}
	else
	{
		--m_isOnSensor;
	}

	if (m_isOnSensor == 0)
	{
		m_arrivalTimer = 0.0f;
	}
}

int PluginGGJ2017::GetLevelClicCount(void)
{
	return(m_iClicCount);
}

/**
* @brief IsWon
*/
bool PluginGGJ2017::IsWon(void)
{
	return(m_isWon);
}

/**
* @brief DatasetParser
* @param pDataSet
*/
void PluginGGJ2017::DatasetParser(ShObject * pObject, ShDataSet * pDataSet)
{
	b2BodyDef bodyDef;
	b2FixtureDef bodyFixture;

	ShObject * pAttachedSprite = shNULL;

	const CShIdentifier & idDataSetIdentifier = ShDataSet::GetDataSetIdentifier(pDataSet);

	int iDataCount = ShDataSet::GetDataCount(pDataSet);
	for (int nData = 0; nData < iDataCount; ++nData)
	{
		//
		// Body
		const CShIdentifier & idDataIdentifier = ShDataSet::GetDataIdentifier(pDataSet, nData);
		if (CShIdentifier("AttachedObject") == idDataIdentifier)
		{
			ShDataSet::GetDataValue(pDataSet, nData, &pAttachedSprite);
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
		else
		{
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
	}

	if (ShObject::GetType(pObject) != ShObject::e_type_unknown)
	{
		bodyDef.angle = ShObject::GetWorldRotation(pObject).m_z;
		bodyDef.position = Convert_sh_b2(ShObject::GetWorldPosition2(pObject));
	}

	Block::EBlockType type = Block::STATIC;
	if (CShIdentifier("sensor_object") == idDataSetIdentifier)
	{
		bodyFixture.isSensor = true;
	}
	else if (CShIdentifier("block_object_player") == idDataSetIdentifier)
	{
		type = Block::PLAYER;
		m_PlayerInitPos = bodyDef.position;
	}
	else if (CShIdentifier("block_object_static") == idDataSetIdentifier)
	{
		type = Block::STATIC;
	}

	b2Body * pBody = m_pWorld->CreateBody(&bodyDef);

	Block * pBlock = new Block();
	pBlock->Initialize(pBody, pAttachedSprite, type);
	m_aBlockList.Add(pBlock);

	pBody->SetUserData(pBlock);

	if (CShIdentifier("block_object_player") == idDataSetIdentifier)
	{
		m_pPlayerBlock = pBlock;
	}

	b2Shape * pShape = GenerateBlockShape(pObject, pBody);
	SH_ASSERT(shNULL != pShape);

	if (shNULL != pShape)
	{
		bodyFixture.shape = pShape;

		b2Fixture * pFixture = pBody->CreateFixture(&bodyFixture);
	}
}

/**
* @brief GenerateBlockShape
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
* @brief GenerateStaticBlockShape
* @param pObject
* @param pBody
*/
b2Shape * PluginGGJ2017::GenerateStaticBlockShape(ShCollisionShape * pShape, b2Body * pBody)
{
	b2ChainShape * pChainShape = new b2ChainShape();

	SH_ASSERT(64 > ShCollisionShape::GetPointCount(pShape));

	b2Vec2 aVertex [64];

	const int pointCount = ShCollisionShape::GetPointCount(pShape);

	for (int i = 0; i < pointCount; ++i)
	{
		const CShVector2 & pos = ShCollisionShape::GetPoint(pShape, i);

		aVertex[i] = Convert_sh_b2(pos);// - pBody->GetPosition();
	}

	pChainShape->CreateLoop(aVertex, pointCount);

	return(pChainShape);
}

/**
* @brief Convert_sh_b2
* @param vec
*/
/*static*/ CShVector2 PluginGGJ2017::Convert_sh_b2(b2Vec2 vec)
{
	return CShVector2(vec.x, vec.y) * CShVector2(ratio_sh_b2, ratio_sh_b2);
}

/**
* @brief Convert_sh_b2
* @param vec
*/
/*static*/ b2Vec2 PluginGGJ2017::Convert_sh_b2(CShVector2 vec)
{
	vec /= CShVector2(ratio_sh_b2, ratio_sh_b2);
	return b2Vec2(vec.m_x, vec.m_y);
}

/**
* @brief UpdateShineObjects
*/
void PluginGGJ2017::UpdateShineObjects(void)
{
	int iBodyCount = m_aBlockList.GetCount();
	for (int nBody = 0; nBody < iBodyCount; ++nBody)
	{
		Block * pBlock = (Block *)m_aBlockList[nBody]->GetBody()->GetUserData();
		ShObject * pObject = pBlock->GetSprite();

		if (shNULL != pObject)
		{
			if (b2_staticBody != m_aBlockList[nBody]->GetBody()->GetType())
			{
				if (ShObject::IsMovable(pObject))
				{
					CShEulerAngles rotAngle(0.0f, 0.0f, m_aBlockList[nBody]->GetBody()->GetAngle());
					ShObject::SetWorldRotation(pObject, rotAngle);

					CShVector2 bodyPos = Convert_sh_b2(m_aBlockList[nBody]->GetBody()->GetPosition());

					ShObject::SetWorldPosition2(pObject, bodyPos);
				}
			}
		}
	}
}

/**
* @brief CheckForAutorRetry
*/
void PluginGGJ2017::CheckForAutoRetry(void)
{
	b2Body * pBody = m_pPlayerBlock->GetBody();
	CShVector2 bodyPos = Convert_sh_b2(pBody->GetPosition());
	// 640 / 360
	if (bodyPos.m_x >= 1136.0f || bodyPos.m_x <= -1136.0f || bodyPos.m_y <= -768.0f)
	{
		Reset();
	}
}

/**
* @brief CapBodyVelocity
*/
void PluginGGJ2017::CapBlockVelocity(float velocityMax)
{
	int iBlockCount = m_aBlockList.GetCount();

	for (int i = 0; i < iBlockCount; ++i)
	{
		if (Block::PLAYER == m_aBlockList[i]->GetType())
		{
			b2Body * pBody = m_aBlockList[i]->GetBody();
			b2Vec2 velocity = pBody->GetLinearVelocity();
			float speed = velocity.Length();

			if (velocityMax < speed)
			{
				pBody->SetLinearVelocity((velocityMax / speed) * velocity);
			}
		}
	}
}
