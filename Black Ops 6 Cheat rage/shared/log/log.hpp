#pragma once

namespace shared::log
{


	/// <summary>
	/// Print given message into console with time in front of it
	/// </summary>
	/// <param name="text">Text which will be printed</param>
	void print( const std::string& text );

	/// <summary>
	/// Print given message into console with time in front of it
	/// </summary>
	/// <param name="text">Text which will be printed</param>
	void print_file( const char* text );

	/// <summary>
	/// Print given message into console with time in front of it
	/// </summary>
	/// <param name="text">Text which will be printed</param>
	void print_file( const std::string& text );

	/// <summary>
	/// Restores original handles and removes the console
	/// </summary>
	void detach();

	void  NotePad(const char* str, ...);
	void log_to_file( const char* str, ...);
}

#if defined( _DEBUG )
#define LOG( text ) shared::log::print_file( text )
#else
#define LOG( text )
#endif