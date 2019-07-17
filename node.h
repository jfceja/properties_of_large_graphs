#include <vector>

class Node {
public:
	Node();

	Node(int m_id);

	Node(int m_id, std::vector<int> m_list);

	bool operator==(const Node& other) const; 

	bool edge_exists(int m_id) const;

	std::vector<int>& get_children();

	std::vector<int> get_children() const;

	int get_m_id() const;

	// I want this to be private but TA mandated it being public & this specific name
	int id;

private:
	std::vector<int> m_list;
};