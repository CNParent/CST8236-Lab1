#include "TransformNode.h"

TransformNode::TransformNode(sf::Shape* shape) : m_Shape(shape) {}

bool TransformNode::Add(TransformNode* child){
	if (child == nullptr || child == this || Has(child)) return false;
	m_Children.push_back(child);
	child->m_Parent = this;
	return true;
}

TransformNode* TransformNode::Get(int i){
	if (m_Children.size() < i + 1) return nullptr;
	return m_Children[i];
}

bool TransformNode::Remove(TransformNode* child){
	bool removed = false;
	if (!Has(child)) return removed;
	auto itr = std::find(m_Children.begin(), m_Children.end(), child);
	if (itr != m_Children.end()){
		m_Children.erase(itr);
		child->m_Parent = nullptr;
		removed = true;
	}
	return removed;
}

bool TransformNode::Has(TransformNode* child){
	// TODO: add recursive check
	auto itr = std::find(m_Children.begin(), m_Children.end(), child);
	return itr != m_Children.end();
}

void TransformNode::Draw(sf::RenderTarget *target, sf::Transform parentTransform) {
    target->draw(*m_Shape, parentTransform);
    auto transform = parentTransform * m_Shape->getTransform();
	for (int i = 0; i < m_Children.size(); i++) 
        m_Children[i]->Draw(target, transform);
}
