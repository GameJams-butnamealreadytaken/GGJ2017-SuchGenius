#include "Plugin.h"

#include "ShSDK/ShSDK.h"

const CShIdentifier plugin_identifier("PluginGGJ2017");

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
 * @brief PluginGGJ2017::OnPlayStart
 * @param levelIdentifier
 */
void PluginGGJ2017::OnPlayStart(const CShIdentifier & levelIdentifier)
{
	// ...
}

/**
 * @brief PluginGGJ2017::OnPlayStop
 * @param levelIdentifier
 */
void PluginGGJ2017::OnPlayStop(const CShIdentifier & levelIdentifier)
{
	// ...
}

/**
* @brief PluginGGJ2017::DatasetParser
* @param pDataSet
*/
void PluginGGJ2017::DatasetParser(ShDataSet * pDataSet)
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

	b2Body * pBody = m_pWorld->CreateBody(&bd);
}