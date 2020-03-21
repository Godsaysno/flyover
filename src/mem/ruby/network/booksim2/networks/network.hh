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

#ifndef _NETWORK_HPP_
#define _NETWORK_HPP_

#include <vector>
#include <deque>

#include "mem/ruby/network/booksim2/module.hh"
#include "mem/ruby/network/booksim2/flit.hh"
#include "mem/ruby/network/booksim2/credit.hh"
/* ==== Power Gate - Begin ==== */
#include "mem/ruby/network/booksim2/handshake.hh"
/* ==== Power Gate - End ==== */
#include "mem/ruby/network/booksim2/routers/router.hh"
#include "mem/ruby/network/booksim2/module.hh"
#include "mem/ruby/network/booksim2/timed_module.hh"
#include "mem/ruby/network/booksim2/flitchannel.hh"
#include "mem/ruby/network/booksim2/channel.hh"
#include "mem/ruby/network/booksim2/config_utils.hh"
#include "mem/ruby/network/booksim2/globals.hh"

typedef Channel<Credit> CreditChannel;
/* ==== Power Gate - Begin ==== */
typedef Channel<Handshake> HandshakeChannel;
/* ==== Power Gate - End ==== */

class BSNetwork : public TimedModule {
protected:

  int _size;
  int _nodes;
  int _channels;
  int _classes;

  vector<Router *> _routers;

  vector<FlitChannel *> _inject;
  vector<CreditChannel *> _inject_cred;

  vector<FlitChannel *> _eject;
  vector<CreditChannel *> _eject_cred;

  vector<FlitChannel *> _chan;
  vector<CreditChannel *> _chan_cred;

  /* ==== Power Gate - Begin ==== */
  int _fabric_manager;  // RP
  bool _powergate_auto_config;
  int _powergate_seed;
  int _powergate_percentile;
  string _powergate_type;
  vector<bool> _core_states;
  vector<bool> _router_states;
  vector<int> _off_cores;
  vector<int> _off_routers;
  vector<HandshakeChannel *> _chan_handshake;
  /* ==== Power Gate - End ==== */

  deque<TimedModule *> _timed_modules;

  virtual void _ComputeSize( const Configuration &config ) = 0;
  virtual void _BuildNet( const Configuration &config ) = 0;

  void _Alloc( );

public:
  BSNetwork( const Configuration &config, const string & name );
  virtual ~BSNetwork( );

  static BSNetwork *New( const Configuration &config, const string & name );

  virtual void WriteFlit( Flit *f, int source );
  virtual Flit *ReadFlit( int dest );

  virtual void    WriteCredit( Credit *c, int dest );
  virtual Credit *ReadCredit( int source );

  inline int NumNodes( ) const {return _nodes;}

  virtual void InsertRandomFaults( const Configuration &config );
  void OutChannelFault( int r, int c, bool fault = true );

  virtual double Capacity( ) const;

  virtual void ReadInputs( );
  /* ==== Power Gate - Begin ==== */
  virtual void PowerStateEvaluate( );
  /* ==== Power Gate - End ==== */
  virtual void Evaluate( );
  virtual void WriteOutputs( );

  // gem5 methods
  virtual bool functionalRead(Packet *pkt);
  virtual uint32_t functionalWrite(Packet *pkt);

  void Display( ostream & os = cout ) const;
  void DumpChannelMap( ostream & os = cout, string const & prefix = "" ) const;
  void DumpNodeMap( ostream & os = cout, string const & prefix = "" ) const;

  int NumChannels() const {return _channels;}
  const vector<FlitChannel *> & GetInject() {return _inject;}
  FlitChannel * GetInject(int index) {return _inject[index];}
  const vector<CreditChannel *> & GetInjectCred() {return _inject_cred;}
  CreditChannel * GetInjectCred(int index) {return _inject_cred[index];}
  const vector<FlitChannel *> & GetEject(){return _eject;}
  FlitChannel * GetEject(int index) {return _eject[index];}
  const vector<CreditChannel *> & GetEjectCred(){return _eject_cred;}
  CreditChannel * GetEjectCred(int index) {return _eject_cred[index];}
  const vector<FlitChannel *> & GetChannels(){return _chan;}
  const vector<CreditChannel *> & GetChannelsCred(){return _chan_cred;}
  /* ==== Power Gate - Begin ==== */
  const vector<HandshakeChannel *> & GetChannelHandshake(){return _chan_handshake;}
  /* ==== Power Gate - End ==== */
  const vector<Router *> & GetRouters(){return _routers;}
  Router * GetRouter(int index) {return _routers[index];}
  int NumRouters() const {return _size;}
  /* ==== Power Gate - Begin ==== */
  vector<bool> & GetCoreStates(){return _core_states;}
  vector<bool> & GetRouterStates(){return _router_states;}
  /* ==== Power Gate - End ==== */
};

#endif 

