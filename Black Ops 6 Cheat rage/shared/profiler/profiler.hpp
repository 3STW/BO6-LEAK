#pragma once

/// TODO: Profiler stuff
namespace shared::profiler
{
	struct node_t
	{
		/// <summary>
		/// Sets up a node with given name
		/// </summary>
		/// <param name="ptr">Name of the node</param>
		node_t( std::string name, std::shared_ptr< node_t > parent ) : m_name( name ), m_parent( parent ), m_children( ) {};

		/// <summary>
		/// Start profiling the node
		/// </summary>
		void start();

		/// <summary>
		/// Stop profiling the node
		/// </summary>
		void stop();

		struct node_data_t
		{
			/// <summary>
			/// The start and ending point
			/// </summary>
			std::chrono::steady_clock::time_point m_start, m_end;
		} m_temp_data;

		/// <summary>
		/// Name of the node
		/// </summary>
		std::string m_name;

		/// <summary>
		/// Are we currently profiling?
		/// </summary>
		bool m_profiling;

		/// <summary>
		/// Data of the current node
		/// </summary>
		std::deque< node_data_t > m_data[ 0xFF ];

		/// <summary>
		/// The parent node
		/// </summary>
		std::shared_ptr< node_t > m_parent;

		/// <summary>
		/// A list of children nodes
		/// </summary>
		std::deque< std::shared_ptr< node_t > > m_children;
	};

	inline std::shared_ptr< node_t > m_root_node, m_active_node;

	/// <summary>
	/// Push a profiling node to the stack
	/// </summary>
	/// <param name="name">The name of the node</param>
	void push_node( std::string name );

	/// <summary>
	/// Pop a profiling node from the stack
	/// </summary>
	void pop_node( );

	/// <summary>
	/// Clear the node stack
	/// </summary>
	void clear_nodes( std::shared_ptr< node_t > nodes = m_root_node );

	/// <summary>
	/// Dump a profiling stack to logs
	/// </summary>
	void dump_nodes( std::shared_ptr< node_t > nodes = m_root_node, int count = 0 );

	struct scope_t
	{
		/// <summary>
		/// Enter a profiling scope
		/// </summary>
		/// <param name="name">The name of the scope</param>
		scope_t( std::string name )
		{
			push_node( name );
		};

		/// <summary>
		/// Exit a profiling scope
		/// </summary>
		~scope_t()
		{
			pop_node();
		};
	};
}