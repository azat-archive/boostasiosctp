//
// sctp_socket_ops.hpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2008 Christopher M. Kohlhoff (chris at kohlhoff dot com)
// Copyright (c) 2009 Hal's Software, Inc. (info at halssoftware dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_SCTP_DETAIL_SCTP_SOCKET_OPS_HPP
#define BOOST_ASIO_SCTP_DETAIL_SCTP_SOCKET_OPS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/push_options.hpp>

#include <boost/asio/detail/push_options.hpp>
#include <boost/config.hpp>
#include <boost/assert.hpp>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <boost/detail/workaround.hpp>
#include <new>
#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/error.hpp>
#include <boost/asio/detail/socket_types.hpp>
#include <boost/asio_sctp/detail/sctp_socket_types.hpp>

namespace boost {
namespace asio_sctp {
namespace detail {
namespace sctp_socket_ops {
using namespace boost::asio::detail;
using namespace boost::asio::detail::socket_ops;

template <typename SockLenType>
inline int call_bind_add(SockLenType msghdr::*,
    socket_type s, const socket_addr_type* addr, std::size_t /* addrlen */)
{
  return ::sctp_bindx(s, const_cast<socket_addr_type*>(addr), 1, SCTP_BINDX_ADD_ADDR);
}

inline int bind_add(socket_type s, const socket_addr_type* addr,
    std::size_t addrlen, boost::system::error_code& ec)
{
  ec.clear();
  int result = error_wrapper(call_bind_add(
        &msghdr::msg_namelen, s, addr, addrlen), ec);
#if defined(BOOST_WINDOWS)
  if (result == 0)
    ec.clear();
#endif
  return result;
}

template <typename SockLenType>
inline int call_bind_remove(SockLenType msghdr::*,
    socket_type s, const socket_addr_type* addr, std::size_t /* addrlen */)
{
  return ::sctp_bindx(s, const_cast<socket_addr_type*>(addr), 1, SCTP_BINDX_REM_ADDR);
}

inline int bind_remove(socket_type s, const socket_addr_type* addr,
    std::size_t addrlen, boost::system::error_code& ec)
{
  ec.clear();
  int result = error_wrapper(call_bind_remove(
        &msghdr::msg_namelen, s, addr, addrlen), ec);
#if defined(BOOST_WINDOWS)
  if (result == 0)
    ec.clear();
#endif
  return result;
}

template <typename SockLenType>
inline int call_getladdrs(SockLenType msghdr::*,
    socket_type s, socket_addr_type** addrs)
{
  int result = ::sctp_getladdrs(s, 0, addrs);
  return result;
}

inline int getladdrs(socket_type s, socket_addr_type** addrs,
    boost::system::error_code& ec)
{
  ec.clear();
  int result = error_wrapper(call_getladdrs(
        &msghdr::msg_namelen, s, addrs), ec);
#if defined(BOOST_WINDOWS)
  if (result == 0)
    ec.clear();
#endif
  return result;
}

inline void freeladdrs(socket_addr_type* addrs)
{
  ::sctp_freeladdrs(addrs);
}

template <typename SockLenType>
inline int call_getpaddrs(SockLenType msghdr::*,
    socket_type s, socket_addr_type** addrs)
{
  int result = ::sctp_getpaddrs(s, 0, addrs);
  return result;
}

inline int getpaddrs(socket_type s, socket_addr_type** addrs,
    boost::system::error_code& ec)
{
  ec.clear();
  int result = error_wrapper(call_getpaddrs(
        &msghdr::msg_namelen, s, addrs), ec);
#if defined(BOOST_WINDOWS)
  if (result == 0)
    ec.clear();
#endif
  return result;
}

inline void freepaddrs(socket_addr_type* addrs)
{
  ::sctp_freepaddrs(addrs);
}

} // namespace sctp_socket_ops
} // namespace detail
} // namespace asio_sctp
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_SCTP_DETAIL_SCTP_SOCKET_OPS_HPP
