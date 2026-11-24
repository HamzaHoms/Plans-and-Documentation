clear all
close all
clc

Tnode_4tx = readtable("1_1u32_15ms.csv");
Tnode_252tx = readtable("1_63u32_120ms.csv");

Tnode_4tx = table2array(Tnode_4tx);
Tnode_252tx = table2array(Tnode_252tx);

Tnode_4rx = readtable("2_1u32_15ms.csv");
Tnode_252rx = readtable("2_63u32_120ms.csv");

Tnode_4rx = table2array(Tnode_4rx);
Tnode_252rx = table2array(Tnode_252rx);


i_t = 1:1:1024;


rc4tx_ts = Tnode_4tx(2051:3074, 1);
rc4rx_ts = Tnode_4rx(2051:3074, 1);

rc252tx_ts = Tnode_252tx(2051:3074, 1);
rc252rx_ts = Tnode_252rx(2051:3074, 1);

rc4tx_avg_delay = mean(diff(rc4tx_ts(1:650)));
rc252tx_avg_delay = mean(diff(rc252tx_ts(1:650)));
rc4rx_avg_delay = mean(diff(rc4rx_ts(1:650)));
rc252rx_avg_delay = mean(diff(rc252rx_ts(1:650)));

rc4tx_ideal_delay = 15488;
rc252tx_ideal_delay = 194688;
rc4rx_ideal_delay = 15488;
rc252rx_ideal_delay = 194688;

p1atx = [4, rc4tx_avg_delay];
p2atx = [252, rc252tx_avg_delay];

p1itx = [4, rc4tx_ideal_delay];
p2itx = [252, rc252tx_ideal_delay];


[matx, batx] = FindLinear(p1atx, p2atx);
[mitx, bitx] = FindLinear(p1itx, p2itx);

p1arx = [4, rc4rx_avg_delay];
p2arx = [252, rc252rx_avg_delay];

p1irx = [4, rc4rx_ideal_delay];
p2irx = [252, rc252rx_ideal_delay];


[marx, barx] = FindLinear(p1arx, p2arx);
[mirx, birx] = FindLinear(p1irx, p2irx);


matx
batx
mitx
bitx

marx
barx
mirx
birx

