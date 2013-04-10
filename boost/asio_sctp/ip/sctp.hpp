//
// sctp.hpp
// ~~~~~~~
//
// Copyright (c) 2003-2008 Christopher M. Kohlhoff (chris at kohlhoff dot com)
// Copyright (c) 2009 Hal's Software, Inc. (info at halssoftware dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_SCTP_IP_SCTP_HPP
#define BOOST_ASIO_SCTP_IP_SCTP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/push_options.hpp>

#include <boost/asio/basic_socket_acceptor.hpp>
#include <boost/asio/socket_acceptor_service.hpp>
#include <boost/asio/basic_socket_iostream.hpp>
#include <boost/asio/basic_stream_socket.hpp>
#include <boost/asio/ip/basic_endpoint.hpp>
#include <boost/asio/ip/basic_resolver.hpp>
#include <boost/asio/ip/basic_resolver_iterator.hpp>
#include <boost/asio/ip/basic_resolver_query.hpp>
#include <boost/asio/detail/socket_option.hpp>
#include <boost/asio/detail/socket_types.hpp>

#include <boost/asio_sctp/sctp_socket_acceptor_service.hpp>
#include <boost/asio_sctp/sctp_socket_acceptor.hpp>
#include <boost/asio_sctp/sctp_stream_socket_service.hpp>
#include <boost/asio_sctp/sctp_stream_socket.hpp>
#include <boost/asio_sctp/detail/sctp_socket_types.hpp>
#include <boost/asio_sctp/detail/sctp_socket_ops.hpp>
#include <vector>

namespace boost {
namespace asio_sctp {
namespace ip {
using namespace boost::asio;
using namespace boost::asio::ip;

/// Encapsulates the flags needed for SCTP.
/**
 * The boost::asio::ip::sctp class contains flags necessary for SCTP sockets.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Safe.
 *
 * @par Concepts:
 * Protocol, InternetProtocol.
 */
class sctp
{
public:
  /// The type of a SCTP endpoint.
  typedef basic_endpoint<sctp> endpoint;

  /// The type of a resolver query.
  typedef basic_resolver_query<sctp> resolver_query;

  /// The type of a resolver iterator.
  typedef basic_resolver_iterator<sctp> resolver_iterator;

  /// Construct to represent the IPv4 SCTP protocol.
  static sctp v4()
  {
    return sctp(PF_INET);
  }

  /// Construct to represent the IPv6 SCTP protocol.
  static sctp v6()
  {
    return sctp(PF_INET6);
  }

  /// Obtain an identifier for the type of the protocol.
  int type() const
  {
    return SOCK_STREAM;
  }

  /// Obtain an identifier for the protocol.
  int protocol() const
  {
    return IPPROTO_SCTP;
  }

  /// Obtain an identifier for the protocol family.
  int family() const
  {
    return family_;
  }

  /// The SCTP socket type.
  typedef basic_stream_socket<sctp> socket;

  /// The SCTP acceptor type.
  typedef sctp_socket_acceptor<sctp> acceptor;

  /// The SCTP resolver type.
  typedef basic_resolver<sctp> resolver;

  /// The SCTP iostream type.
  typedef basic_socket_iostream<sctp> iostream;

  /// Socket option for disabling the Nagle algorithm.
  /**
   * Implements the IPPROTO_SCTP/SCTP_NODELAY socket option.
   *
   * @par Examples
   * Setting the option:
   * @code
   * boost::asio::ip::sctp::socket socket(io_service); 
   * ...
   * boost::asio::ip::sctp::no_delay option(true);
   * socket.set_option(option);
   * @endcode
   *
   * @par
   * Getting the current option value:
   * @code
   * boost::asio::ip::sctp::socket socket(io_service); 
   * ...
   * boost::asio::ip::sctp::no_delay option;
   * socket.get_option(option);
   * bool is_set = option.value();
   * @endcode
   *
   * @par Concepts:
   * Socket_Option, Boolean_Socket_Option.
   */
#if defined(GENERATING_DOCUMENTATION)
  typedef implementation_defined no_delay;
#else
  typedef boost::asio::detail::socket_option::boolean<
    IPPROTO_SCTP, SCTP_NODELAY> no_delay;
#endif

  /// Compare two protocols for equality.
  friend bool operator==(const sctp& p1, const sctp& p2)
  {
    return p1.family_ == p2.family_;
  }

  /// Compare two protocols for inequality.
  friend bool operator!=(const sctp& p1, const sctp& p2)
  {
    return p1.family_ != p2.family_;
  }

private:
  // Construct with a specific family.
  explicit sctp(int family)
    : family_(family)
  {
  }

  int family_;
};

} // namespace ip
} // namespace asio_sctp
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_SCTP_IP_SCTP_HPP

