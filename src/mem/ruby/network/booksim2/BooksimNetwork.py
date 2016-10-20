from m5.params import *
from m5.proxy import *
from Network import RubyNetwork
from ClockedObject import ClockedObject

class BooksimNetwork(RubyNetwork):
    type = 'BooksimNetwork'
    cxx_header = "mem/ruby/network/booksim2/BooksimNetwork.hh"

    attached_router_id = VectorParam.Int("Node router association map")
    booksim_config = Param.String("configs/ruby_booksim/gem5booksim.cfg",
                                  "path to booksim config file")
