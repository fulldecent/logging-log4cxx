/***************************************************************************
                          socketoutputstream.h  -  SocketOutputStream
                             -------------------
    begin                : ven mai 9 2003
    copyright            : (C) 2003 by Michael CATANZARITI
    email                : mcatan@free.fr
 ***************************************************************************/

/***************************************************************************
 * Copyright (C) The Apache Software Foundation. All rights reserved.      *
 *                                                                         *
 * This software is published under the terms of the Apache Software       *
 * License version 1.1, a copy of which has been included with this        *
 * distribution in the LICENSE.txt file.                                   *
 ***************************************************************************/

#ifndef _LOG4CXX_HELPERS_SOCKET_OUTPUT_STREAM_H
#define _LOG4CXX_HELPERS_SOCKET_OUTPUT_STREAM_H

#include <log4cxx/helpers/tchar.h>
#include <log4cxx/helpers/objectimpl.h>
#include <log4cxx/helpers/objectptr.h>

namespace log4cxx
{
	namespace helpers
	{
		class Socket;
		typedef ObjectPtrT<Socket> SocketPtr;
		
		class SocketOutputStream;
		typedef ObjectPtrT<SocketOutputStream> SocketOutputStreamPtr;
		
		class LOG4CXX_EXPORT SocketOutputStream : public ObjectImpl
		{
		public:
			DECLARE_ABSTRACT_LOG4CXX_OBJECT(SocketOutputStream)
			BEGIN_LOG4CXX_CAST_MAP()
				LOG4CXX_CAST_ENTRY(SocketOutputStream)
			END_LOG4CXX_CAST_MAP()

			SocketOutputStream(SocketPtr socket);
			~SocketOutputStream();
			
			void write(const void * buffer, size_t len);
			void write(unsigned int value);
			void write(int value);
			void write(unsigned long value);
			void write(long value);
			void write(const String& value);
			// some write functions are missing ...

			/** Close the stream and dereference the socket.
			*/
			void close();

			/** Flushes this output stream and forces any buffered output
			bytes to be written out.
			*/
			void flush();

		protected:
			SocketPtr socket;

			/** memory stream buffer */
/*			class membuf :
				public std::basic_streambuf<char, std::char_traits<char> >
			{
			public:
				const void * buffer() const;
				const size_t size() const;
			}*/

			unsigned char * beg, * cur, * end;
		};
	}; // namespace helpers
}; // namespace log4cxx

#endif // _LOG4CXX_HELPERS_SOCKET_OUTPUT_STREAM_H
