//
// sctp_stream_socket.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2008 Christopher M. Kohlhoff (chris at kohlhoff dot com)
// Copyright (c) 2009 Hal's Software, Inc. (info at halssoftware dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_SCTP_SCTP_STREAM_SOCKET_HPP
#define BOOST_ASIO_SCTP_SCTP_STREAM_SOCKET_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/push_options.hpp>

#include <boost/asio/basic_stream_socket.hpp>
#include <boost/asio_sctp/sctp_stream_socket_service.hpp>
#include <boost/asio_sctp/detail/sctp_socket_types.hpp>
#include <boost/asio_sctp/detail/sctp_socket_ops.hpp>
#include <vector>

namespace boost {
namespace asio_sctp {
using namespace boost::asio;

template <typename Protocol>
class sctp_stream_socket
  : public basic_stream_socket<Protocol, sctp_stream_socket_service<Protocol> >
{
public:
   typedef typename basic_stream_socket<Protocol, sctp_stream_socket_service<Protocol> >::protocol_type protocol_type;
   typedef typename basic_stream_socket<Protocol, sctp_stream_socket_service<Protocol> >::endpoint_type endpoint_type;
   typedef typename basic_stream_socket<Protocol, sctp_stream_socket_service<Protocol> >::native_type native_type;

   /// Construct a basic_stream_socket without opening it.
   explicit sctp_stream_socket(boost::asio::io_service& io_service)
     : basic_stream_socket<Protocol, sctp_stream_socket_service<Protocol> >(io_service)
   {
   }

   /// Construct and open a basic_stream_socket.
   sctp_stream_socket(boost::asio::io_service& io_service,
       const protocol_type& protocol)
     : basic_stream_socket<Protocol, sctp_stream_socket_service<Protocol> >(io_service, protocol)
   {
   }

   /// Construct a basic_stream_socket, opening it and binding it to the given
   /// local endpoint.
   sctp_stream_socket(boost::asio::io_service& io_service,
       const endpoint_type& endpoint)
     : basic_stream_socket<Protocol, sctp_stream_socket_service<Protocol> >(io_service, endpoint)
   {
   }

   /// Construct a basic_stream_socket on an existing native socket.
   sctp_stream_socket(boost::asio::io_service& io_service,
       const protocol_type& protocol,
       const native_type& native_socket)
     : basic_stream_socket<Protocol, sctp_stream_socket_service<Protocol> >(
         io_service, protocol, native_socket)
   {
   }

   /// Get the local endpoints of the socket.
   /**
    * This function is used to obtain the locally bound endpoints of the socket.
    *
    * @param endpoints A vector to hold the local endpoints of the socket.
    *
    * @throws boost::system::system_error Thrown on failure.
    *
    * @par Example
    * @code
    * boost::asio::ip::sctp::socket socket(io_service);
    * ...
    * std::vector<boost::asio::ip::sctp::endpoint> endpoints;
    * socket.local_endpoints(endpoints);
    * @endcode
    */
   void local_endpoints(std::vector<endpoint_type> &endpoints) const
   {
     boost::system::error_code ec;
     this->service.local_endpoints(this->implementation, endpoints, ec);
     boost::asio::detail::throw_error(ec);
   }

   /// Get the local endpoints of the socket.
   /**
    * This function is used to obtain the locally bound endpoints of the socket.
    *
    * @param endpoints A vector to hold the local endpoints of the socket.
    * @param ec Set to indicate what error occurred, if any.
    *
    * @par Example
    * @code
    * boost::asio::ip::sctp::socket socket(io_service);
    * ...
    * boost::system::error_code ec;
    * std::vector<boost::asio::ip::sctp::endpoint> endpoints;
    * socket.local_endpoints(endpoints, ec);
    * if (ec)
    * {
    *   // An error occurred.
    * }
    * @endcode
    */
   void local_endpoints(std::vector<endpoint_type> &endpoints,
      boost::system::error_code& ec) const
   {
     this->service.local_endpoints(this->implementation, endpoints, ec);
   }

   /// Get the remote endpoints of the socket.
   /**
    * This function is used to obtain the remote endpoints of the socket.
    *
    * @param endpoints A vector to hold the remote endpoints of the socket.
    *
    * @throws boost::system::system_error Thrown on failure.
    *
    * @par Example
    * @code
    * boost::asio::ip::sctp::socket socket(io_service);
    * ...
    * std::vector<boost::asio::ip::sctp::endpoint> endpoints;
    * socket.remote_endpoints(endpoints);
    * @endcode
    */
   void remote_endpoints(std::vector<endpoint_type> &endpoints) const
   {
     boost::system::error_code ec;
     this->service.remote_endpoints(this->implementation, endpoints, ec);
     boost::asio::detail::throw_error(ec);
   }

   /// Get the remote endpoints of the socket.
   /**
    * This function is used to obtain the remote endpoints of the socket.
    *
    * @param endpoints A vector to hold the remote endpoints of the socket.
    * @param ec Set to indicate what error occurred, if any.
    *
    * @par Example
    * @code
    * boost::asio::ip::sctp::socket socket(io_service);
    * ...
    * boost::system::error_code ec;
    * std::vector<boost::asio::ip::sctp::endpoint> endpoints;
    * socket.remote_endpoints(endpoints, ec);
    * if (ec)
    * {
    *   // An error occurred.
    * }
    * @endcode
    */
   void remote_endpoints(std::vector<endpoint_type> &endpoints,
      boost::system::error_code& ec) const
   {
     this->service.remote_endpoints(this->implementation, endpoints, ec);
   }

};

} // namespace asio_sctp
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_SCTP_SCTP_STREAM_SOCKET_HPP

