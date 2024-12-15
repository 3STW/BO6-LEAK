#include "../shared.hpp"

namespace shared::profiler
{
	void node_t::start()
	{
		/// Set the profiling flag to true
		m_profiling = true;

		/// Store the starting time
		m_temp_data.m_start = std::chrono::high_resolution_clock::now();
	}

	void node_t::stop()
	{
		/// Store the end time
	/*	m_temp_data.m_end = std::chrono::high_resolution_clock::now();

		/// Add the temporary data to the data list
		m_data[ GImGui->FrameCount % 0xFF ].push_back( m_temp_data );

		/// Clear the profiling flag
		m_profiling = false;*/
	}

	void push_node( std::string name )
	{
		auto node = std::make_shared< node_t >( name, m_active_node );
		
		if ( m_root_node == nullptr )
			m_root_node = node;

		if ( m_active_node )
			m_active_node->m_children.push_back( node );

		m_active_node = node;

		m_active_node->start();
	}

	void pop_node()
	{
		m_active_node->stop();

		m_active_node = m_active_node->m_parent;
	}

	void clear_nodes( std::shared_ptr< node_t > node )
	{
		if ( node != nullptr )
		{
			node->m_children.clear();
			node.reset();
		}

		if ( m_root_node != nullptr )
			m_root_node.reset();

		if ( m_active_node != nullptr )
			m_active_node.reset();
	}

	void dump_nodes( std::shared_ptr< node_t > node, int count )
	{
		/// Output the node
		LOG( fmt::format( "{} -> {}", count, node->m_name ) );

		/// Make sure we have nodes to iterate
		if ( node->m_children.size() <= 0 )
			return;

		for ( auto child_node : node->m_children )
		{
			/// Dump the children nodes
			dump_nodes( child_node, count + 1 );
		}

		/// Clear all the nodes.
		clear_nodes( node );
	}
}