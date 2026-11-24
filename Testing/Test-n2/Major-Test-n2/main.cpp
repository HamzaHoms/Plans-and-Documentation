#include <iostream>
#include <vector>
#include <queue>
#include <random>


class Packet
{
public:
	uint32_t dest;
	uint32_t src;
	uint32_t size;

	uint32_t hops;

	bool failed;

	uint64_t start;
	uint64_t finish;
};


#define FIFOS_SIZE 512
#define RADIO_BUFFER_SIZE 255

class FIFO 
{
public:
	uint32_t cnt;
	uint32_t max_size;

	std::queue<Packet> packets;

	FIFO(uint32_t fifo_size)
	{
		this->max_size = fifo_size;
	}

	void Push(Packet& packet)
	{
		this->packets.push(packet);
		this->cnt += packet.size;
	}
	
	Packet Pop()
	{
		Packet packet = this->packets.front();
		this->packets.pop();

		this->cnt -= packet.size;

		return packet;
	}
};


typedef enum {
	UART_CLEAR = 0,
	UART_BUSY = 1
} UART_States;

typedef enum {
	RADIO_CLEAR = 0,
	RADIO_TX = 1,
	RADIO_RX = 2
} Radio_States;

class Node
{
public:
	FIFO in_uart_fifo = FIFO(FIFOS_SIZE);
	UART_States in_uart_sts;
	uint64_t in_uart_next_step;

	FIFO out_uart_fifo = FIFO(FIFOS_SIZE);
	UART_States out_uart_sts;
	uint64_t out_uart_next_step;


	FIFO radio_buf = FIFO(RADIO_BUFFER_SIZE);
	Radio_States radio_sts;
	uint64_t radio_next_step;


	std::vector<Node> neighbors;

	uint32_t x, y;

	
};



#define UART_SVC_T(n) ( 8 + 20 * (n) )
#define RADIO_SVC_T(n) ( 15900 + 512 * (n) )
#define ROUTING_SVC_T(n) ( 15000 )

#define NODE_RANGE 100
#define NODE_COUNT 10

#define SIM_TIME_S 10

#define W_H 600
#define W_W 600

int main(void)
{

	//Node Generation Stage
	std::vector<Node> nodes;

	std::srand(std::time({}));

	for (int i = 0; i < NODE_COUNT; i++)
	{
		Node node;
		node.x = std::rand() % W_W;
		node.y = std::rand() % W_H;

		nodes.push_back(node);
	}

	for (Node& nodei : nodes)
	{
		for (Node& nodej : nodes)
		{
			if (nodei.x == nodej.x && nodei.y == nodej.y) continue;

			if (std::hypot(nodei.x - nodej.x, nodei.y - nodej.y) < NODE_RANGE) nodei.neighbors.push_back(nodej);
		}
	}

	//Sim Stage
	uint64_t us_ts = 0;
	std::vector<Packet&> packets;

	for (; us_ts < SIM_TIME_S * 1000000; us_ts++)
	{
		if (us_ts % 100000)
		{
			Packet packet;
			packet.src = std::rand() % NODE_COUNT;
			do {
				packet.dest = std::rand() % NODE_COUNT;
			} while (packet.dest == packet.src);
			packet.hops = 0;
			packet.size = 4;
			packet.start = us_ts;

			packets.push_back(packet);

			nodes[packet.src].out_uart_fifo.Push(packet);
		}

		
		for (Node& node : nodes)
		{
			if (node.out_uart_sts == UART_BUSY && node.out_uart_next_step == us_ts)
			{
				Packet packet = node.out_uart_fifo.Pop();
			}
		}

	}
}