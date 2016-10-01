#ifndef _TRANSFORM_NODE_H
#define _TRANSFORM_NODE_H

#include <vector>
#include <SFML\Graphics.hpp>

class TransformNode
{
public:

	TransformNode(sf::Shape* shape);
	////~TransformNode();

	bool Add(TransformNode* child);
	TransformNode* Get(int i);
	bool Remove(TransformNode* child);
	bool Has(TransformNode* child);
	
	void Draw(sf::RenderTarget *target, sf::Transform parentTransform = sf::Transform::Identity);

protected:

	std::vector<TransformNode*> m_Children;
	TransformNode* m_Parent;
	sf::Shape *m_Shape;

};

#endif
