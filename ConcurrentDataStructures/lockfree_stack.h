#pragma once

#include <atomic>
#include <memory>

template<typename T>
struct node
{
	std::shared_ptr<T> data;
	node* next;

	node(const T& _data)
		: data(std::make_shared<T>(_data)), next(nullptr)
	{
	}
};

template<typename T>
class lock_free_stack
{
public:
	void push(const T& data)
	{
		const node* new_node = new node(T);
		new_node->next() = head.load();
		while(!head.compare_exchange_weak(new_node->next, new_node));
	}

	std::shared_ptr<T> pop()
	{
		++threads_in_pop;

		node* headNode = head.load();
		while( headNode != nullptr &&
			!head.compare_exchange_weak(headNode, headNode->next));

		std::shared_ptr<T> result;
		if (headNode != nullptr) {
			result.swap(headNode->data);
		}
		try_reclaim(headNode);
		return result;
	}

private:
	std::atomic<node*> head;
	std::atomic<unsigned> threads_in_pop;
	std::atomic<node*> to_delete;

	void try_reclaim(node* old_head);
	void chain_pending_nodes(node* nodes);
	void chain_pending_nodes(node* first, node* last);
	void chain_pending_node(node* node);
};

template<typename T>
static void delete_nodes(node<T>* nodes)
{
	while (nodes) {
		node* next = nodes->next;
		delete nodes;
		nodes = next;
	}
}

template<typename T>
inline void lock_free_stack<T>::try_reclaim(node<T>* old_head)
{
	if (threads_in_pop == 1) {		
		node* nodes_to_delete = to_delete.exchange(nullptr);
		if(!--threads_in_pop)
			delete_nodes(nodes_to_delete);
		else if(nodes_to_delete)
			chain_pending_nodes(nodes_to_delete);
		delete old_head;
	} else {
		chain_pending_node(old_head);
		--threads_in_pop;
	}
}

template<typename T>
inline void lock_free_stack<T>::chain_pending_nodes(node<T>* nodes)
{
	node* last = nodes;
	while(const node* next = last->next)
		last = next;
	chain_pending_nodes(nodes, last);
}

template<typename T>
inline void lock_free_stack<T>::chain_pending_nodes(node<T>* first, node<T>* last)
{
	last->next = to_delete;
	while(!to_delete.compare_exchange_weak(
		last->next,first));
}

template<typename T>
inline void lock_free_stack<T>::chain_pending_node(node<T>* node)
{
	chain_pending_nodes(node, node);
}
