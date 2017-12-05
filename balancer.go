package balancer

import (
        "net"
	"fmt"
)

type Server struct {
    Name string
    Scheme string
    Host string
    Port string
    Connections int
}

func (g *greeter)SayHi(context.Context, *pb.Empty) (*pb.HiMessage, error) {
	return &pb.HiMessage{g.s}, nil
}

func (server Server) Url() string {
  return server.Scheme + "://" + server.Host + ":" + server.Port;
}