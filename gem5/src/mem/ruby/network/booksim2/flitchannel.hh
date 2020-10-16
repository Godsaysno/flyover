// $Id$

/*
 Copyright (c) 2007-2015, Trustees of The Leland Stanford Junior University
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:

 Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.
 Redistributions in binary form must reproduce the above copyright notice, this
 list of conditions and the following disclaimer in the documentation and/or
 other materials provided with the distribution.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

// ----------------------------------------------------------------------
//
//  File Name: flitchannel.hpp
//
//  The FlitChannel models a flit channel with a multi-cycle
//   transmission delay. The channel latency can be specified as
//   an integer number of simulator cycles.
// ----------------------------------------------------------------------

#ifndef FLITCHANNEL_HPP
#define FLITCHANNEL_HPP

// ----------------------------------------------------------------------
//  $Author: jbalfour $
//  $Date: 2007/06/27 23:10:17 $
//  $Id$
// ----------------------------------------------------------------------

#include "mem/ruby/network/booksim2/channel.hh"
#include "mem/ruby/network/booksim2/flit.hh"

using namespace std;

class BSRouter ;

class FlitChannel : public Channel<Flit> {
public:
  FlitChannel(Module * parent, string const & name, int classes);

  /* ==== Power Gate - Begin ==== */
  //void SetSource(BSRouter const * const router, int port) ;
  //inline BSRouter const * const GetSource() const {
  //  return _routerSource;
  //}
  void SetSource(BSRouter * router, int port) ;
  inline BSRouter * GetSource() const {
    return _routerSource;
  }
  /* ==== Power Gate - End ==== */
  inline int const & GetSourcePort() const {
    return _routerSourcePort;
  }
  /* ==== Power Gate - Begin ==== */
  //void SetSink(BSRouter const * const router, int port) ;
  //inline BSRouter const * const GetSink() const {
  //  return _routerSink;
  //}
  void SetSink(BSRouter * router, int port) ;
  inline BSRouter * GetSink() const {
    return _routerSink;
  }
  /* ==== Power Gate - End ==== */
  inline int const & GetSinkPort() const {
    return _routerSinkPort;
  }
  inline vector<uint64_t> const & GetActivity() const {
    return _active;
  }

  // Send flit
  virtual void Send(Flit * flit);

  virtual void ReadInputs();
  virtual void WriteOutputs();

  // gem5 functional methods
  virtual bool functionalRead(Packet *pkt);
  virtual uint32_t functionalWrite(Packet *pkt);

private:

  ////////////////////////////////////////
  //
  // Power Models OBSOLETE
  //
  ////////////////////////////////////////

  /* ==== Power Gate - Begin ==== */
  //BSRouter const * _routerSource;
  BSRouter * _routerSource;
  /* ==== Power Gate - End ==== */
  int _routerSourcePort;
  /* ==== Power Gate - Begin ==== */
  //BSRouter const * _routerSink;
  BSRouter * _routerSink;
  /* ==== Power Gate - End ==== */
  int _routerSinkPort;

  // Statistics for Activity Factors
  vector<uint64_t> _active;
  uint64_t _idle;
};

#endif
