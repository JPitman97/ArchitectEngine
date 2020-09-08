#include "Entity.h"
#include "Core.h"
#include "RendererComponent.h"
#include "VertexBuffer.h"
#include "MeshCollision.h"

void MeshCollision::onTick()
{
	//tri_tri_overlap_test_3d();
	if (isStatic == false)
	{
		for (auto& entity : getEntity()->getCore()->getEntities())
		{
			if (entity->getComponent<MeshCollision>() && this->getEntity() != entity)
			{
				std::vector<float> meshVertices = entity->getComponent<RendererComponent>()->getobjPositions()->GetData();
				int meshComp = entity->getComponent<RendererComponent>()->getobjPositions()->GetComponents();
				std::vector<float> thisVerts = this->getEntity()->getComponent<RendererComponent>()->getobjPositions()->GetData();
				if (meshComp == 3)
				{
					for (int i = 0; i < thisVerts.size(); i + 9)
					{
						for (int j = 0; j < meshVertices.size(); j + 9)
						{
							float p1Arr[3] = { thisVerts[i], thisVerts[i + 1], thisVerts[i + 2] };
							float p2Arr[3] = { thisVerts[i+3], thisVerts[i + 4], thisVerts[i + 5] };
							float p3Arr[3] = { thisVerts[i+6], thisVerts[i + 7], thisVerts[i + 8] };

							float q1Arr[3] = { meshVertices[j], meshVertices[j + 1], meshVertices[j + 2] };
							float q2Arr[3] = { meshVertices[j + 3], meshVertices[j + 4], meshVertices[j + 5] };
							float q3Arr[3] = { meshVertices[j + 6], meshVertices[j + 7], meshVertices[j + 8] };

							if (tri_tri_overlap_test_3d(p1Arr, p2Arr, p3Arr, q1Arr, q2Arr, q3Arr))
							{
								std::cout << "Mesh collision made" << std::endl;
								return;
							}
						}
					}
				}
			}
		}
	}
}
