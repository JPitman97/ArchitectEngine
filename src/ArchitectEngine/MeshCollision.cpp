#include "Entity.h"
#include "Core.h"
#include "RendererComponent.h"
#include "TransformComponent.h"
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
				//Get actual world positions of these vertices!
				std::vector<float> thisVerts = this->getEntity()->getComponent<RendererComponent>()->getobjPositions()->GetData();
				std::vector<float> meshVertices = entity->getComponent<RendererComponent>()->getobjPositions()->GetData();
				int meshComp = entity->getComponent<RendererComponent>()->getobjPositions()->GetComponents();
				if (meshComp == 3)
				{
					for (int i = 0; i < thisVerts.size(); i += 9)
					{
						for (int j = 0; j < meshVertices.size(); j+=9)
						{
							glm::vec3 p1 = glm::vec3(thisVerts[i] + this->getEntity()->getComponent<TransformComponent>()->getPos().x,
								thisVerts[i + 1] + this->getEntity()->getComponent<TransformComponent>()->getPos().y,
								thisVerts[i + 2] + this->getEntity()->getComponent<TransformComponent>()->getPos().z);
							glm::vec3 p2 = glm::vec3(thisVerts[i + 3] + this->getEntity()->getComponent<TransformComponent>()->getPos().x,
								thisVerts[i + 4] + this->getEntity()->getComponent<TransformComponent>()->getPos().y,
								thisVerts[i + 5] + this->getEntity()->getComponent<TransformComponent>()->getPos().z);
							glm::vec3 p3 = glm::vec3(thisVerts[i + 6] + this->getEntity()->getComponent<TransformComponent>()->getPos().x,
								thisVerts[i + 7] + this->getEntity()->getComponent<TransformComponent>()->getPos().y,
								thisVerts[i + 8] + this->getEntity()->getComponent<TransformComponent>()->getPos().z);
							float p1Arr[3] = { p1.x, p1.y, p1.z };
							float p2Arr[3] = { p2.x, p2.y, p2.z };
							float p3Arr[3] = { p3.x, p3.y, p3.z };

							glm::vec3 q1 = glm::vec3(meshVertices[j] + entity->getComponent<TransformComponent>()->getPos().x,
								meshVertices[j + 1] + entity->getComponent<TransformComponent>()->getPos().y,
								meshVertices[j + 2] + entity->getComponent<TransformComponent>()->getPos().z);
							glm::vec3 q2 = glm::vec3(meshVertices[j + 3] + entity->getComponent<TransformComponent>()->getPos().x,
								meshVertices[j + 4] + entity->getComponent<TransformComponent>()->getPos().y,
								meshVertices[j + 5] + entity->getComponent<TransformComponent>()->getPos().z);
							glm::vec3 q3 = glm::vec3(meshVertices[j + 6] + entity->getComponent<TransformComponent>()->getPos().x,
								meshVertices[j + 7] + entity->getComponent<TransformComponent>()->getPos().y,
								meshVertices[j + 8] + entity->getComponent<TransformComponent>()->getPos().z);
							float q1Arr[3] = { q1.x, q1.y, q1.z };
							float q2Arr[3] = { q2.x, q2.y, q2.z };
							float q3Arr[3] = { q3.x, q3.y, q3.z };

							if (tri_tri_overlap_test_3d(p1Arr, p2Arr, p3Arr, q1Arr, q2Arr, q3Arr) == 1)
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
