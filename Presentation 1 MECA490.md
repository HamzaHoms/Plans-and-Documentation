Guidelines :
-6 slides
-5 research papers
-4 minutes

Points I would like to showcase :
- Explain the difference between the different control structures
- Show the structures in the context of control
- Show the structures in the context of communication

Points I would like to emphasize about my project :
- Separation of the control layer and communication layer
- End-point indifference and support for multiple devices
- Decentralization of communication and abstraction of control

Paper Notes :
Check [[Presentation 1 Research Paper Notes]]

Slide Outline :
1) Title page : Project Title, My Name.
2) Robotic swarm control structures : Centralized vs Decentralized vs Manual https://www.europhysicsnews.org/articles/epn/full_html/2026/03/epn2026573p16/epn2026573p16.html
3) Communication Layer Details : Centralized vs Decentralized in the context of communication, and issues. https://web.stanford.edu/class/cs244/papers/DistributedCommunicationsNetworks.pdf, https://pmc.ncbi.nlm.nih.gov/articles/PMC7435450/pdf/sensors-20-04273.pdf.
4) Control Layer Details : Centralized vs Decentralized in the context of control, and levels of autonomy/sliding autonomy. https://scispace.com/pdf/coordinated-multiagent-teams-and-sliding-autonomy-for-large-4j2getapf4.pdf, https://www.researchgate.net/publication/269785177_A_Survey_and_Analysis_of_Multi-Robot_Coordination.
5) Robot swarms in the industry : Show some examples from the research papers (1) & (3) and about how robot swarms usually show up in the industry.
6) My project, how it works briefly, and how it combines the best of both worlds.
7) Emphasis on the separation of the control layer and communication layer, and the indifference to end-point variance.

Slide Plan, The long part :

(1) What I would like to say : "Greetings, Today I would like to give an intro about Decentralized mesh of companion computers for autonomous vehicles and devices, which will be my senior design project."

The slide : Title, Name.

(2) What I want to say : "Starting off I need to showcase the two most common structures for command and control of robot swarms, centralized and decentralized. Centralized is when there is a single operator commanding each target through a direct link, and Decentralized is where the operator commands the targets indirectly through repeating links and independent control logic"

The slide : two images side-by-side of a centralized network and a decentralized network, with text under each that briefly says what I already spoke.

(3) What I want to say : "Let's look at the two structures in the context of communication. first off a direct comparison on a network made of nodes, let's say that each node could fall off the network due to a failure, centralized is a lot less resilient in this regard, as the central node falling off the network means the whole network goes down, meanwhile decentralized leaves the surrounding nodes of a failed node connected due to the redundant connects, as this graph{1} showcases, as the number of redundant connections increase a node can stay on the network for longer even when more of it's neighbors fall off. One way of achieving this is through multi-hop communication, where intermediate nodes relay packets toward their destination. Research into LoRaWAN mesh networks has explored exactly this approach, using relay and router nodes to extend communication beyond a direct end-device-to-gateway link."

The slide : 4 points that say : "-Centralized networks fail with the failure of a single node \n -Decentralized networks can stay online for longer because they don't have any central weakpoints \n -decentralized networks can route messages over longer distances by utilizing repeater nodes \n -messages hop through repeater nodes until they reach their destination". Then a graph{1} under them which is Fig.4 of the Paul Baran Paper.

(4) What I want to say : "How about a control context of the two structures? Centralized is able to have a global memory of all targets, and a sort of overview, and often shows more optimal results while giving the operator the ability to directly control the targets, but is again fragile to the central controller failing, and hard to scale. however Decentralized is a lot more adaptable and splits the workflow between the targets allowing for smooth transition of control even if a featured "central overseer" fails, but usually shows sub-optimal results for the tasks performed, and kind of locks the operator out of direct manual control and requires heavier automation. So there is no clear winner here."

The slide : 2 comparison columns : Under centralized control "pros : precise, simple logic flow, global overview of the targets. cons : single point of failure, hard to scale.", under decentralized control "pros : robust, easily scalable, easy task hand-off. cons : less precise in execution, requires more autonomous decision-making.".

(5) What I want to say : "Now that we've seen theory, let's look at what the industry says. As this drone swarm researcher says, most drone swarms in applications like light shows and military end up using a centralized control and communication system. Decentralized systems have not seen the industry standardization that were expected of them due to constraints related to their chaotic nature and complexity. Something to note here is that most industry applications use the same structure for both control and communication. But what if we didn't? What if we separated both of those layers?"

The slide : a direct quote from research paper (1). 

(6) What I want to say : "This is where my project comes in. I have decided to completely separate the communication and control layers.
The communication layer is a decentralized mesh network, where each node acts both as a packet repeater, and as an endpoint that can directly communicate with the target.
The control layer, meanwhile, is left for the end user to configure through custom scripts. these custom scripts can vary the control logic and the level of autonomy, giving each separate target in the network a sliding level of autonomy, while the communication layer remains completely untouched.
In other words, the way the system communicates does not have to change just because the way the system is controlled changes."

The slide : some bulletpoints with "-decentralized \n -Variable autonomy \n Separation of layers" or something similar, then an animated diagram that starts with a connection between target and companion computer, then zooming out to show the companion computer in a network with colored arrows representing the packets going over the network.

(7) What I want to say : "This freedom in control also has a positive side-effect : end-point indifference. The companion computer can be configured to work with a wide-range of targets, this way many different targets can sit on the same network and talk to each other, like drones, rovers, sensor stations, repeater stations."

The slide : A slide showing different drawings connected to the computer flashing, then zooming out to a network with multiple different end-point types on it.