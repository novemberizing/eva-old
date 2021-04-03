----

TCP 에서 WRITE 가 완료되었다는 것은 WRITE 버퍼에 데이터를 보내고 그 크기가 작아진 것이다. (TCP 는 재전송로직이 존재하여 상대방의 버퍼에 보낸 것을 확인할 때까지 데이터를 가지고 재전송을 수행하기 때문이다.) 그렇기 때문에, WRITE 버퍼가 보낸 데이터 만큼 작아졌다는 것은 상대방의 버퍼에 데이터가 삽입되었다는 것을 의미한다. 이런 개념을 가지고 WRITE 성공 타임을 체크할 수 있어 보인다.

---- 

OPTIMIZE -O3

event on => in / [ 0.940596084 , 100000 ]
event on => in / | 0.940596084 | 100000 |
event on => in / [ 1.820353458 , 200000 ]
event on => in / | 1.820353458 | 200000 |
event on => in / [ 2.733714130 , 300000 ]
event on => in / | 2.733714130 | 300000 |
event on => in / [ 3.611127217 , 400000 ]
event on => in / | 3.611127217 | 400000 |
event on => in / [ 4.533357816 , 500000 ]
event on => in / | 4.533357816 | 500000 |
event on => in / [ 5.473605806 , 600000 ]
event on => in / | 5.473605806 | 600000 |
event on => in / [ 6.350033932 , 700000 ]
event on => in / | 6.350033932 | 700000 |
event on => in / [ 7.238972878 , 800000 ]
event on => in / | 7.238972878 | 800000 |
event on => in / [ 8.116593564 , 900000 ]
event on => in / | 8.116593564 | 900000 |
event on => in / [ 8.995510275 , 1000000 ]
event on => in / | 8.995510275 | 1000000 |
event on => in / [ 9.867615356 , 1100000 ]
event on => in / | 9.867615356 | 1100000 |
event on => in / [ 10.747375043 , 1200000 ]
event on => in / | 10.747375043 | 1200000 |
event on => in / [ 11.626770389 , 1300000 ]
event on => in / | 11.626770389 | 1300000 |
event on => in / [ 12.509011504 , 1400000 ]
event on => in / | 12.509011504 | 1400000 |
event on => in / [ 13.762262889 , 1500000 ]
event on => in / | 13.762262889 | 1500000 |
event on => in / [ 14.644457291 , 1600000 ]
event on => in / | 14.644457291 | 1600000 |
event on => in / [ 15.531695780 , 1700000 ]
event on => in / | 15.531695780 | 1700000 |
event on => in / [ 16.564819334 , 1800000 ]
event on => in / | 16.564819334 | 1800000 |
event on => in / [ 17.449798525 , 1900000 ]
event on => in / | 17.449798525 | 1900000 |
event on => in / [ 18.331373107 , 2000000 ]
event on => in / | 18.331373107 | 2000000 |
event on => in / [ 19.213318413 , 2100000 ]
event on => in / | 19.213318413 | 2100000 |
event on => in / [ 20.262019300 , 2200000 ]
event on => in / | 20.262019300 | 2200000 |
event on => in / [ 21.214486424 , 2300000 ]
event on => in / | 21.214486424 | 2300000 |
event on => in / [ 22.099601186 , 2400000 ]
event on => in / | 22.099601186 | 2400000 |
event on => in / [ 22.980924205 , 2500000 ]
event on => in / | 22.980924205 | 2500000 |
event on => in / [ 23.852673526 , 2600000 ]
event on => in / | 23.852673526 | 2600000 |
event on => in / [ 24.754433622 , 2700000 ]
event on => in / | 24.754433622 | 2700000 |
event on => in / [ 25.631941268 , 2800000 ]
event on => in / | 25.631941268 | 2800000 |
event on => in / [ 26.505055192 , 2900000 ]
event on => in / | 26.505055192 | 2900000 |
event on => in / [ 27.637039089 , 3000000 ]
event on => in / | 27.637039089 | 3000000 |
event on => in / [ 28.696762264 , 3100000 ]
event on => in / | 28.696762264 | 3100000 |
event on => in / [ 29.586131821 , 3200000 ]
event on => in / | 29.586131821 | 3200000 |
event on => in / [ 31.009337808 , 3300000 ]
event on => in / | 31.009337808 | 3300000 |
event on => in / [ 32.479458140 , 3400000 ]
event on => in / | 32.479458140 | 3400000 |
event on => in / [ 33.365447488 , 3500000 ]
event on => in / | 33.365447488 | 3500000 |
event on => in / [ 34.313935621 , 3600000 ]
event on => in / | 34.313935621 | 3600000 |
event on => in / [ 35.580628009 , 3700000 ]
event on => in / | 35.580628009 | 3700000 |
event on => in / [ 37.081660458 , 3800000 ]
event on => in / | 37.081660458 | 3800000 |
event on => in / [ 38.059808427 , 3900000 ]
event on => in / | 38.059808427 | 3900000 |
event on => in / [ 38.959732605 , 4000000 ]
event on => in / | 38.959732605 | 4000000 |
event on => in / [ 39.863073083 , 4100000 ]
event on => in / | 39.863073083 | 4100000 |
event on => in / [ 40.760014813 , 4200000 ]
event on => in / | 40.760014813 | 4200000 |
event on => in / [ 41.650160204 , 4300000 ]
event on => in / | 41.650160204 | 4300000 |
event on => in / [ 42.546052911 , 4400000 ]
event on => in / | 42.546052911 | 4400000 |
event on => in / [ 43.437905039 , 4500000 ]
event on => in / | 43.437905039 | 4500000 |
event on => in / [ 44.329231188 , 4600000 ]
event on => in / | 44.329231188 | 4600000 |
event on => in / [ 45.242186947 , 4700000 ]
event on => in / | 45.242186947 | 4700000 |
event on => in / [ 46.121469565 , 4800000 ]
event on => in / | 46.121469565 | 4800000 |
event on => in / [ 47.029999250 , 4900000 ]
event on => in / | 47.029999250 | 4900000 |
event on => in / [ 47.914755837 , 5000000 ]
event on => in / | 47.914755837 | 5000000 |
event on => in / [ 48.808047783 , 5100000 ]
event on => in / | 48.808047783 | 5100000 |
event on => in / [ 49.704303472 , 5200000 ]
event on => in / | 49.704303472 | 5200000 |
event on => in / [ 50.790583946 , 5300000 ]
event on => in / | 50.790583946 | 5300000 |
event on => in / [ 51.677448749 , 5400000 ]
event on => in / | 51.677448749 | 5400000 |
event on => in / [ 52.565699214 , 5500000 ]
event on => in / | 52.565699214 | 5500000 |
event on => in / [ 53.454500860 , 5600000 ]
event on => in / | 53.454500860 | 5600000 |
event on => in / [ 54.351415826 , 5700000 ]
event on => in / | 54.351415826 | 5700000 |
event on => in / [ 55.443055528 , 5800000 ]
event on => in / | 55.443055528 | 5800000 |
event on => in / [ 56.335171887 , 5900000 ]
event on => in / | 56.335171887 | 5900000 |
event on => in / [ 57.218089289 , 6000000 ]
event on => in / | 57.218089289 | 6000000 |
event on => in / [ 58.331179073 , 6100000 ]
event on => in / | 58.331179073 | 6100000 |
event on => in / [ 59.731684623 , 6200000 ]
event on => in / | 59.731684623 | 6200000 |
event on => in / [ 60.849520109 , 6300000 ]
event on => in / | 60.849520109 | 6300000 |
event on => in / [ 61.822841868 , 6400000 ]
event on => in / | 61.822841868 | 6400000 |

----






event on => in / | 26.606171128 | 2100000 |



event on => in / | 27.967637395 | 2200000 |



event on => in / [ 26.606171128 , 2100000 ]
event on => in / [ 27.967637395 , 2200000 ]

event on => in / [ 29.242359645 , 2300000 ]
event on => in / | 29.242359645 | 2300000 |
event on => in / [ 30.619824738 , 2400000 ]
event on => in / | 30.619824738 | 2400000 |
event on => in / [ 32.167531284 , 2500000 ]
event on => in / | 32.167531284 | 2500000 |
event on => in / [ 33.234030489 , 2600000 ]
event on => in / | 33.234030489 | 2600000 |
event on => in / [ 34.208868905 , 2700000 ]
event on => in / | 34.208868905 | 2700000 |
event on => in / [ 35.136329702 , 2800000 ]
event on => in / | 35.136329702 | 2800000 |
event on => in / [ 36.086613888 , 2900000 ]
event on => in / | 36.086613888 | 2900000 |
event on => in / [ 37.001629904 , 3000000 ]
event on => in / | 37.001629904 | 3000000 |
event on => in / [ 37.917091325 , 3100000 ]
event on => in / | 37.917091325 | 3100000 |
event on => in / [ 39.090911813 , 3200000 ]
event on => in / | 39.090911813 | 3200000 |
event on => in / [ 40.201207606 , 3300000 ]
event on => in / | 40.201207606 | 3300000 |
event on => in / [ 41.121670649 , 3400000 ]
event on => in / | 41.121670649 | 3400000 |
event on => in / [ 42.182010589 , 3500000 ]
event on => in / | 42.182010589 | 3500000 |
event on => in / [ 43.114667864 , 3600000 ]
event on => in / | 43.114667864 | 3600000 |
event on => in / [ 44.040671925 , 3700000 ]
event on => in / | 44.040671925 | 3700000 |
event on => in / [ 44.956375340 , 3800000 ]
event on => in / | 44.956375340 | 3800000 |
event on => in / [ 45.896931185 , 3900000 ]
event on => in / | 45.896931185 | 3900000 |
event on => in / [ 47.051640388 , 4000000 ]
event on => in / | 47.051640388 | 4000000 |
event on => in / [ 48.041976362 , 4100000 ]
event on => in / | 48.041976362 | 4100000 |
event on => in / [ 48.959182574 , 4200000 ]
event on => in / | 48.959182574 | 4200000 |
event on => in / [ 49.874360842 , 4300000 ]
event on => in / | 49.874360842 | 4300000 |
event on => in / [ 50.790934048 , 4400000 ]
event on => in / | 50.790934048 | 4400000 |
event on => in / [ 51.713221633 , 4500000 ]
event on => in / | 51.713221633 | 4500000 |
event on => in / [ 52.632490914 , 4600000 ]
event on => in / | 52.632490914 | 4600000 |
event on => in / [ 53.565525242 , 4700000 ]
event on => in / | 53.565525242 | 4700000 |
event on => in / [ 54.536933550 , 4800000 ]
event on => in / | 54.536933550 | 4800000 |
event on => in / [ 55.456635210 , 4900000 ]
event on => in / | 55.456635210 | 4900000 |
event on => in / [ 56.409709332 , 5000000 ]
event on => in / | 56.409709332 | 5000000 |
event on => in / [ 57.327453351 , 5100000 ]
event on => in / | 57.327453351 | 5100000 |
event on => in / [ 58.247963645 , 5200000 ]
event on => in / | 58.247963645 | 5200000 |
event on => in / [ 59.353508029 , 5300000 ]
event on => in / | 59.353508029 | 5300000 |
event on => in / [ 60.394700191 , 5400000 ]
event on => in / | 60.394700191 | 5400000 |
event on => in / [ 61.364646589 , 5500000 ]
event on => in / | 61.364646589 | 5500000 |
event on => in / [ 62.679424513 , 5600000 ]
event on => in / | 62.679424513 | 5600000 |
event on => in / [ 63.596067130 , 5700000 ]
event on => in / | 63.596067130 | 5700000 |
event on => in / [ 64.512472360 , 5800000 ]
event on => in / | 64.512472360 | 5800000 |
event on => in / [ 65.428423630 , 5900000 ]
event on => in / | 65.428423630 | 5900000 |
event on => in / [ 66.349365734 , 6000000 ]
event on => in / | 66.349365734 | 6000000 |
event on => in / [ 67.265574519 , 6100000 ]
event on => in / | 67.265574519 | 6100000 |
event on => in / [ 68.185005460 , 6200000 ]
event on => in / | 68.185005460 | 6200000 |
event on => in / [ 69.101715365 , 6300000 ]
event on => in / | 69.101715365 | 6300000 |
event on => in / [ 70.018203562 , 6400000 ]
event on => in / | 70.018203562 | 6400000 |
event on => in / [ 70.936814313 , 6500000 ]
event on => in / | 70.936814313 | 6500000 |
event on => in / [ 71.856023320 , 6600000 ]
event on => in / | 71.856023320 | 6600000 |
event on => in / [ 72.773906208 , 6700000 ]
event on => in / | 72.773906208 | 6700000 |
event on => in / [ 74.024436628 , 6800000 ]
event on => in / | 74.024436628 | 6800000 |

----


event on => in / [2.187177305 , 200000]
event on => in / | 2.187177305 | 200000 |
event on => in / [4.039020540 , 400000]
event on => in / | 4.039020540 | 400000 |
event on => in / [5.890541373 , 600000]
event on => in / | 5.890541373 | 600000 |
event on => in / [7.747209592 , 800000]
event on => in / | 7.747209592 | 800000 |
event on => in / [9.595638718 , 1000000]
event on => in / | 9.595638718 | 1000000 |
event on => in / [12.075148053 , 1200000]
event on => in / | 12.075148053 | 1200000 |
event on => in / [13.931401787 , 1400000]
event on => in / | 13.931401787 | 1400000 |
event on => in / [15.793378680 , 1600000]
event on => in / | 15.793378680 | 1600000 |
event on => in / [17.688611180 , 1800000]
event on => in / | 17.688611180 | 1800000 |
event on => in / [19.540924839 , 2000000]
event on => in / | 19.540924839 | 2000000 |
event on => in / [21.370476228 , 2200000]
event on => in / | 21.370476228 | 2200000 |
event on => in / [23.199086479 , 2400000]
event on => in / | 23.199086479 | 2400000 |
event on => in / [25.042867401 , 2600000]
event on => in / | 25.042867401 | 2600000 |
event on => in / [26.867963482 , 2800000]
event on => in / | 26.867963482 | 2800000 |
event on => in / [28.694509937 , 3000000]
event on => in / | 28.694509937 | 3000000 |
event on => in / [30.516808890 , 3200000]
event on => in / | 30.516808890 | 3200000 |
event on => in / [32.342032479 , 3400000]
event on => in / | 32.342032479 | 3400000 |
event on => in / [34.169689374 , 3600000]
event on => in / | 34.169689374 | 3600000 |
event on => in / [36.023972398 , 3800000]
event on => in / | 36.023972398 | 3800000 |
event on => in / [37.847823001 , 4000000]
event on => in / | 37.847823001 | 4000000 |
event on => in / [39.676242756 , 4200000]
event on => in / | 39.676242756 | 4200000 |
event on => in / [41.501043817 , 4400000]
event on => in / | 41.501043817 | 4400000 |
event on => in / [43.326346687 , 4600000]
event on => in / | 43.326346687 | 4600000 |
event on => in / [45.289833606 , 4800000]
event on => in / | 45.289833606 | 4800000 |
event on => in / [47.186123988 , 5000000]
event on => in / | 47.186123988 | 5000000 |
event on => in / [49.013830335 , 5200000]
event on => in / | 49.013830335 | 5200000 |
event on => in / [50.843300903 , 5400000]
event on => in / | 50.843300903 | 5400000 |
event on => in / [52.772728448 , 5600000]
event on => in / | 52.772728448 | 5600000 |

----

- [ ]

----

- [ ] 멀티 엔진 클라이언트 
- [ ] session socket close 시에 REMOVE 를 설정할 수 있도록 하자. 과연 어디에서 해야할까?

----

READ/WRITE 시에

WRITE ALL > READ ONCE > WRITE ALL - 그리고 in 상태이면 큐에 넣고, 아니면 등록을 하자.

----

eva> 

==91790== 
==91790== HEAP SUMMARY:
==91790==     in use at exit: 293,520 bytes in 265 blocks
==91790==   total heap usage: 310 allocs, 45 frees, 339,382 bytes allocated
==91790== 
==91790== 32 bytes in 1 blocks are still reachable in loss record 1 of 17
==91790==    at 0x483DD99: calloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==91790==    by 0x111BD1: xclientpoollist_new (list.c:10)
==91790==    by 0x10E0C9: xdescriptoreventgenerator_clientpool_add (generator.c:16)
==91790==    by 0x10C653: xeventengine_clientpool_add (engine.c:389)
==91790==    by 0x10A8AA: main (engine.c:45)
==91790== 
==91790== 48 bytes in 1 blocks are still reachable in loss record 2 of 17
==91790==    at 0x483DD99: calloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==91790==    by 0x116669: xstreambuffer_new (buffer.c:30)
==91790==    by 0x115502: xstreamnew (stream.c:39)
==91790==    by 0x10FF6B: xconsoleinit (console.c:102)
==91790==    by 0x10B384: xeventengine_run (engine.c:68)
==91790==    by 0x10A8CC: main (engine.c:49)
==91790== 
==91790== 48 bytes in 1 blocks are still reachable in loss record 3 of 17
==91790==    at 0x483DD99: calloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==91790==    by 0x116669: xstreambuffer_new (buffer.c:30)
==91790==    by 0x115502: xstreamnew (stream.c:39)
==91790==    by 0x10FF88: xconsoleinit (console.c:107)
==91790==    by 0x10B384: xeventengine_run (engine.c:68)
==91790==    by 0x10A8CC: main (engine.c:49)
==91790== 
==91790== 64 bytes in 1 blocks are still reachable in loss record 4 of 17
==91790==    at 0x483DD99: calloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==91790==    by 0x10E295: xdescriptoreventgenerator_new (epoll.c:24)
==91790==    by 0x10B1AD: xeventengine_new (engine.c:34)
==91790==    by 0x10A828: main (engine.c:36)
==91790== 
==91790== 64 bytes in 1 blocks are still reachable in loss record 5 of 17
==91790==    at 0x483DD99: calloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==91790==    by 0x1116B6: xclientpoolnew (pool.c:22)
==91790==    by 0x10A83D: main (engine.c:38)
==91790== 
==91790== 64 bytes in 1 blocks are still reachable in loss record 6 of 17
==91790==    at 0x483DD99: calloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==91790==    by 0x1180C1: xeventsubscription_new (subscription.c:17)
==91790==    by 0x10BF36: xeventengine_descriptor_register (engine.c:264)
==91790==    by 0x10B3D7: xeventengine_run (engine.c:78)
==91790==    by 0x10A8CC: main (engine.c:49)
==91790== 
==91790== 64 bytes in 1 blocks are still reachable in loss record 7 of 17
==91790==    at 0x483DD99: calloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==91790==    by 0x1180C1: xeventsubscription_new (subscription.c:17)
==91790==    by 0x10BF36: xeventengine_descriptor_register (engine.c:264)
==91790==    by 0x10B3EA: xeventengine_run (engine.c:79)
==91790==    by 0x10A8CC: main (engine.c:49)
==91790== 
==91790== 512 bytes in 32 blocks are still reachable in loss record 8 of 17
==91790==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==91790==    by 0x114221: xobjectdup (object.c:81)
==91790==    by 0x111EDA: xclientsocket_new (socket.c:40)
==91790==    by 0x111209: xclientnew (client.c:27)
==91790==    by 0x10A877: main (engine.c:42)
==91790== 
==91790== 512 bytes in 32 blocks are still reachable in loss record 9 of 17
==91790==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==91790==    by 0x1166A3: xstreambuffer_new (buffer.c:35)
==91790==    by 0x115502: xstreamnew (stream.c:39)
==91790==    by 0x112142: xclientsocketconnect (socket.c:91)
==91790==    by 0x112801: xclientsocketprocess_open (tcp.c:119)
==91790==    by 0x112657: xclientsocketprocess_tcp (tcp.c:63)
==91790==    by 0x10E7A2: xdescriptoreventgenerator_queue_once (epoll.c:137)
==91790==    by 0x10E438: xdescriptoreventgenerator_once (epoll.c:66)
==91790==    by 0x10CF71: xeventgeneratorset_once (set.c:46)
==91790==    by 0x10B435: xeventengine_run (engine.c:90)
==91790==    by 0x10A8CC: main (engine.c:49)
==91790== 
==91790== 1,536 bytes in 32 blocks are still reachable in loss record 10 of 17
==91790==    at 0x483DD99: calloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==91790==    by 0x116669: xstreambuffer_new (buffer.c:30)
==91790==    by 0x115502: xstreamnew (stream.c:39)
==91790==    by 0x11211D: xclientsocketconnect (socket.c:86)
==91790==    by 0x112801: xclientsocketprocess_open (tcp.c:119)
==91790==    by 0x112657: xclientsocketprocess_tcp (tcp.c:63)
==91790==    by 0x10E7A2: xdescriptoreventgenerator_queue_once (epoll.c:137)
==91790==    by 0x10E438: xdescriptoreventgenerator_once (epoll.c:66)
==91790==    by 0x10CF71: xeventgeneratorset_once (set.c:46)
==91790==    by 0x10B435: xeventengine_run (engine.c:90)
==91790==    by 0x10A8CC: main (engine.c:49)
==91790== 
==91790== 1,536 bytes in 32 blocks are still reachable in loss record 11 of 17
==91790==    at 0x483DD99: calloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==91790==    by 0x116669: xstreambuffer_new (buffer.c:30)
==91790==    by 0x115502: xstreamnew (stream.c:39)
==91790==    by 0x112142: xclientsocketconnect (socket.c:91)
==91790==    by 0x112801: xclientsocketprocess_open (tcp.c:119)
==91790==    by 0x112657: xclientsocketprocess_tcp (tcp.c:63)
==91790==    by 0x10E7A2: xdescriptoreventgenerator_queue_once (epoll.c:137)
==91790==    by 0x10E438: xdescriptoreventgenerator_once (epoll.c:66)
==91790==    by 0x10CF71: xeventgeneratorset_once (set.c:46)
==91790==    by 0x10B435: xeventengine_run (engine.c:90)
==91790==    by 0x10A8CC: main (engine.c:49)
==91790== 
==91790== 2,048 bytes in 32 blocks are still reachable in loss record 12 of 17
==91790==    at 0x483DD99: calloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==91790==    by 0x1111E2: xclientnew (client.c:25)
==91790==    by 0x10A877: main (engine.c:42)
==91790== 
==91790== 2,048 bytes in 32 blocks are still reachable in loss record 13 of 17
==91790==    at 0x483DD99: calloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==91790==    by 0x1180C1: xeventsubscription_new (subscription.c:17)
==91790==    by 0x10BB37: xeventengine_client_register (engine.c:209)
==91790==    by 0x10E117: xdescriptoreventgenerator_clientpool_add (generator.c:23)
==91790==    by 0x10C653: xeventengine_clientpool_add (engine.c:389)
==91790==    by 0x10A8AA: main (engine.c:45)
==91790== 
==91790== 5,888 bytes in 32 blocks are still reachable in loss record 14 of 17
==91790==    at 0x483DD99: calloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==91790==    by 0x111E40: xclientsocket_new (socket.c:24)
==91790==    by 0x111209: xclientnew (client.c:27)
==91790==    by 0x10A877: main (engine.c:42)
==91790== 
==91790== 8,192 bytes in 1 blocks are still reachable in loss record 15 of 17
==91790==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==91790==    by 0x116F88: xstreambuffer_adjust (buffer.c:344)
==91790==    by 0x11622A: xstreamadjust (stream.c:416)
==91790==    by 0x10D7A9: xdescriptorstreamread (descriptor.c:279)
==91790==    by 0x110556: xconsoledescriptoreventprocessorin_in (in.c:124)
==91790==    by 0x110483: xconsoledescriptoreventprocessorin_void (in.c:89)
==91790==    by 0x1103D7: xconsoledescriptoreventprocessorin (in.c:67)
==91790==    by 0x1187FE: xdescriptoreventdispatch_void (dispatch.c:40)
==91790==    by 0x10E5D6: xdescriptoreventgenerator_once (epoll.c:98)
==91790==    by 0x10CF71: xeventgeneratorset_once (set.c:46)
==91790==    by 0x10B435: xeventengine_run (engine.c:90)
==91790==    by 0x10A8CC: main (engine.c:49)
==91790== 
==91790== 8,208 bytes in 1 blocks are still reachable in loss record 16 of 17
==91790==    at 0x483DFAF: realloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==91790==    by 0x116B7C: xstreambuffercapacity_set (buffer.c:184)
==91790==    by 0x115B51: xstreamcapacity_set (stream.c:228)
==91790==    by 0x110E4F: xconsoledescriptoreventprocessorout_flush (out.c:186)
==91790==    by 0x110B45: xconsoledescriptoreventprocessorout_void (out.c:87)
==91790==    by 0x110AA2: xconsoledescriptoreventprocessorout (out.c:67)
==91790==    by 0x1102CE: xconsoleout (console.c:167)
==91790==    by 0x112F52: xevacli (cli.c:109)
==91790==    by 0x1101A7: xconsoledescriptoron (console.c:147)
==91790==    by 0x10CFD8: xdescriptoron (descriptor.c:26)
==91790==    by 0x10D87A: xdescriptorstreamread (descriptor.c:293)
==91790==    by 0x110556: xconsoledescriptoreventprocessorin_in (in.c:124)
==91790== 
==91790== 262,656 bytes in 32 blocks are still reachable in loss record 17 of 17
==91790==    at 0x483DFAF: realloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==91790==    by 0x116B7C: xstreambuffercapacity_set (buffer.c:184)
==91790==    by 0x115B51: xstreamcapacity_set (stream.c:228)
==91790==    by 0x10D7F0: xdescriptorstreamread (descriptor.c:282)
==91790==    by 0x112860: xclientsocketprocess_in (tcp.c:127)
==91790==    by 0x112701: xclientsocketprocess_void (tcp.c:85)
==91790==    by 0x112657: xclientsocketprocess_tcp (tcp.c:63)
==91790==    by 0x1187FE: xdescriptoreventdispatch_void (dispatch.c:40)
==91790==    by 0x10E7AE: xdescriptoreventgenerator_queue_once (epoll.c:138)
==91790==    by 0x10E438: xdescriptoreventgenerator_once (epoll.c:66)
==91790==    by 0x10CF71: xeventgeneratorset_once (set.c:46)
==91790==    by 0x10B435: xeventengine_run (engine.c:90)
==91790== 
==91790== LEAK SUMMARY:
==91790==    definitely lost: 0 bytes in 0 blocks
==91790==    indirectly lost: 0 bytes in 0 blocks
==91790==      possibly lost: 0 bytes in 0 blocks
==91790==    still reachable: 293,520 bytes in 265 blocks
==91790==         suppressed: 0 bytes in 0 blocks
==91790== 
==91790== For lists of detected and suppressed errors, rerun with: -s
==91790== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
hyunsik@hyunsik-aspire:~/Workspace/novemberizing/eva$ 


eva> ==89879== 
==89879== HEAP SUMMARY:
==89879==     in use at exit: 293,520 bytes in 265 blocks
==89879==   total heap usage: 310 allocs, 45 frees, 339,382 bytes allocated
==89879== 
==89879== 32 bytes in 1 blocks are still reachable in loss record 1 of 17
==89879==    at 0x483DD99: calloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==89879==    by 0x111ADB: xclientpoollist_new (list.c:10)
==89879==    by 0x10E0BF: xdescriptoreventgenerator_clientpool_add (generator.c:16)
==89879==    by 0x10C649: xeventengine_clientpool_add (engine.c:389)
==89879==    by 0x10A8AA: main (engine.c:45)
==89879== 
==89879== 48 bytes in 1 blocks are still reachable in loss record 2 of 17
==89879==    at 0x483DD99: calloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==89879==    by 0x116573: xstreambuffer_new (buffer.c:30)
==89879==    by 0x11540C: xstreamnew (stream.c:39)
==89879==    by 0x10FF61: xconsoleinit (console.c:102)
==89879==    by 0x10B37A: xeventengine_run (engine.c:68)
==89879==    by 0x10A8CC: main (engine.c:49)
==89879== 
==89879== 48 bytes in 1 blocks are still reachable in loss record 3 of 17
==89879==    at 0x483DD99: calloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==89879==    by 0x116573: xstreambuffer_new (buffer.c:30)
==89879==    by 0x11540C: xstreamnew (stream.c:39)
==89879==    by 0x10FF7E: xconsoleinit (console.c:107)
==89879==    by 0x10B37A: xeventengine_run (engine.c:68)
==89879==    by 0x10A8CC: main (engine.c:49)
==89879== 
==89879== 64 bytes in 1 blocks are still reachable in loss record 4 of 17
==89879==    at 0x483DD99: calloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==89879==    by 0x10E28B: xdescriptoreventgenerator_new (epoll.c:24)
==89879==    by 0x10B1A3: xeventengine_new (engine.c:34)
==89879==    by 0x10A828: main (engine.c:36)
==89879== 
==89879== 64 bytes in 1 blocks are still reachable in loss record 5 of 17
==89879==    at 0x483DD99: calloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==89879==    by 0x1116AC: xclientpoolnew (pool.c:22)
==89879==    by 0x10A83D: main (engine.c:38)
==89879== 
==89879== 64 bytes in 1 blocks are still reachable in loss record 6 of 17
==89879==    at 0x483DD99: calloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==89879==    by 0x117FCB: xeventsubscription_new (subscription.c:17)
==89879==    by 0x10BF2C: xeventengine_descriptor_register (engine.c:264)
==89879==    by 0x10B3CD: xeventengine_run (engine.c:78)
==89879==    by 0x10A8CC: main (engine.c:49)
==89879== 
==89879== 64 bytes in 1 blocks are still reachable in loss record 7 of 17
==89879==    at 0x483DD99: calloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==89879==    by 0x117FCB: xeventsubscription_new (subscription.c:17)
==89879==    by 0x10BF2C: xeventengine_descriptor_register (engine.c:264)
==89879==    by 0x10B3E0: xeventengine_run (engine.c:79)
==89879==    by 0x10A8CC: main (engine.c:49)
==89879== 
==89879== 512 bytes in 32 blocks are still reachable in loss record 8 of 17
==89879==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==89879==    by 0x11412B: xobjectdup (object.c:81)
==89879==    by 0x111DE4: xclientsocket_new (socket.c:40)
==89879==    by 0x1111FF: xclientnew (client.c:27)
==89879==    by 0x10A877: main (engine.c:42)
==89879== 
==89879== 512 bytes in 32 blocks are still reachable in loss record 9 of 17
==89879==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==89879==    by 0x1165AD: xstreambuffer_new (buffer.c:35)
==89879==    by 0x11540C: xstreamnew (stream.c:39)
==89879==    by 0x11204C: xclientsocketconnect (socket.c:91)
==89879==    by 0x11270B: xclientsocketprocess_open (tcp.c:119)
==89879==    by 0x112561: xclientsocketprocess_tcp (tcp.c:63)
==89879==    by 0x10E798: xdescriptoreventgenerator_queue_once (epoll.c:137)
==89879==    by 0x10E42E: xdescriptoreventgenerator_once (epoll.c:66)
==89879==    by 0x10CF67: xeventgeneratorset_once (set.c:46)
==89879==    by 0x10B42B: xeventengine_run (engine.c:90)
==89879==    by 0x10A8CC: main (engine.c:49)
==89879== 
==89879== 1,536 bytes in 32 blocks are still reachable in loss record 10 of 17
==89879==    at 0x483DD99: calloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==89879==    by 0x116573: xstreambuffer_new (buffer.c:30)
==89879==    by 0x11540C: xstreamnew (stream.c:39)
==89879==    by 0x112027: xclientsocketconnect (socket.c:86)
==89879==    by 0x11270B: xclientsocketprocess_open (tcp.c:119)
==89879==    by 0x112561: xclientsocketprocess_tcp (tcp.c:63)
==89879==    by 0x10E798: xdescriptoreventgenerator_queue_once (epoll.c:137)
==89879==    by 0x10E42E: xdescriptoreventgenerator_once (epoll.c:66)
==89879==    by 0x10CF67: xeventgeneratorset_once (set.c:46)
==89879==    by 0x10B42B: xeventengine_run (engine.c:90)
==89879==    by 0x10A8CC: main (engine.c:49)
==89879== 
==89879== 1,536 bytes in 32 blocks are still reachable in loss record 11 of 17
==89879==    at 0x483DD99: calloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==89879==    by 0x116573: xstreambuffer_new (buffer.c:30)
==89879==    by 0x11540C: xstreamnew (stream.c:39)
==89879==    by 0x11204C: xclientsocketconnect (socket.c:91)
==89879==    by 0x11270B: xclientsocketprocess_open (tcp.c:119)
==89879==    by 0x112561: xclientsocketprocess_tcp (tcp.c:63)
==89879==    by 0x10E798: xdescriptoreventgenerator_queue_once (epoll.c:137)
==89879==    by 0x10E42E: xdescriptoreventgenerator_once (epoll.c:66)
==89879==    by 0x10CF67: xeventgeneratorset_once (set.c:46)
==89879==    by 0x10B42B: xeventengine_run (engine.c:90)
==89879==    by 0x10A8CC: main (engine.c:49)
==89879== 
==89879== 2,048 bytes in 32 blocks are still reachable in loss record 12 of 17
==89879==    at 0x483DD99: calloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==89879==    by 0x1111D8: xclientnew (client.c:25)
==89879==    by 0x10A877: main (engine.c:42)
==89879== 
==89879== 2,048 bytes in 32 blocks are still reachable in loss record 13 of 17
==89879==    at 0x483DD99: calloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==89879==    by 0x117FCB: xeventsubscription_new (subscription.c:17)
==89879==    by 0x10BB2D: xeventengine_client_register (engine.c:209)
==89879==    by 0x10E10D: xdescriptoreventgenerator_clientpool_add (generator.c:23)
==89879==    by 0x10C649: xeventengine_clientpool_add (engine.c:389)
==89879==    by 0x10A8AA: main (engine.c:45)
==89879== 
==89879== 5,888 bytes in 32 blocks are still reachable in loss record 14 of 17
==89879==    at 0x483DD99: calloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==89879==    by 0x111D4A: xclientsocket_new (socket.c:24)
==89879==    by 0x1111FF: xclientnew (client.c:27)
==89879==    by 0x10A877: main (engine.c:42)
==89879== 
==89879== 8,192 bytes in 1 blocks are still reachable in loss record 15 of 17
==89879==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==89879==    by 0x116E92: xstreambuffer_adjust (buffer.c:344)
==89879==    by 0x116134: xstreamadjust (stream.c:416)
==89879==    by 0x10D79F: xdescriptorstreamread (descriptor.c:279)
==89879==    by 0x11054C: xconsoledescriptoreventprocessorin_in (in.c:124)
==89879==    by 0x110479: xconsoledescriptoreventprocessorin_void (in.c:89)
==89879==    by 0x1103CD: xconsoledescriptoreventprocessorin (in.c:67)
==89879==    by 0x118708: xdescriptoreventdispatch_void (dispatch.c:40)
==89879==    by 0x10E5CC: xdescriptoreventgenerator_once (epoll.c:98)
==89879==    by 0x10CF67: xeventgeneratorset_once (set.c:46)
==89879==    by 0x10B42B: xeventengine_run (engine.c:90)
==89879==    by 0x10A8CC: main (engine.c:49)
==89879== 
==89879== 8,208 bytes in 1 blocks are still reachable in loss record 16 of 17
==89879==    at 0x483DFAF: realloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==89879==    by 0x116A86: xstreambuffercapacity_set (buffer.c:184)
==89879==    by 0x115A5B: xstreamcapacity_set (stream.c:228)
==89879==    by 0x110E45: xconsoledescriptoreventprocessorout_flush (out.c:186)
==89879==    by 0x110B3B: xconsoledescriptoreventprocessorout_void (out.c:87)
==89879==    by 0x110A98: xconsoledescriptoreventprocessorout (out.c:67)
==89879==    by 0x1102C4: xconsoleout (console.c:167)
==89879==    by 0x112E5C: xevacli (cli.c:109)
==89879==    by 0x11019D: xconsoledescriptoron (console.c:147)
==89879==    by 0x10CFCE: xdescriptoron (descriptor.c:26)
==89879==    by 0x10D870: xdescriptorstreamread (descriptor.c:293)
==89879==    by 0x11054C: xconsoledescriptoreventprocessorin_in (in.c:124)
==89879== 
==89879== 262,656 bytes in 32 blocks are still reachable in loss record 17 of 17
==89879==    at 0x483DFAF: realloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==89879==    by 0x116A86: xstreambuffercapacity_set (buffer.c:184)
==89879==    by 0x115A5B: xstreamcapacity_set (stream.c:228)
==89879==    by 0x10D7E6: xdescriptorstreamread (descriptor.c:282)
==89879==    by 0x11276A: xclientsocketprocess_in (tcp.c:127)
==89879==    by 0x11260B: xclientsocketprocess_void (tcp.c:85)
==89879==    by 0x112561: xclientsocketprocess_tcp (tcp.c:63)
==89879==    by 0x118708: xdescriptoreventdispatch_void (dispatch.c:40)
==89879==    by 0x10E7A4: xdescriptoreventgenerator_queue_once (epoll.c:138)
==89879==    by 0x10E42E: xdescriptoreventgenerator_once (epoll.c:66)
==89879==    by 0x10CF67: xeventgeneratorset_once (set.c:46)
==89879==    by 0x10B42B: xeventengine_run (engine.c:90)
==89879== 
==89879== LEAK SUMMARY:
==89879==    definitely lost: 0 bytes in 0 blocks
==89879==    indirectly lost: 0 bytes in 0 blocks
==89879==      possibly lost: 0 bytes in 0 blocks
==89879==    still reachable: 293,520 bytes in 265 blocks
==89879==         suppressed: 0 bytes in 0 blocks
==89879== 
==89879== For lists of detected and suppressed errors, rerun with: -s
==89879== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)


----

- [ ] 콘솔 디스크립터 아웃은 커맨드 입력 모드에서는 동작하지 않도록 한다.
- [ ] 디스크립터 인/아웃에 대하여 이벤트 핸들링에 대하여 리팩토링을 하자.

----

- [ ] SESSION
- [ ] SERVER
- [ ] CONSOLE
- [ ] SIGNAL

----

- [ ] SIGPIPE 에 대한 처리 (예외가 발생하는구나.)
- [ ] 클라이언트 풀 (수평적 분할 / 수직적 분할)

----

- [ ] 지금까지의 구현을 정리하자. (그림으로 적당히...)

----

- [ ] 디스크립터의 체크 함수는 지울까 사용할까 고민이 된다.

        현재까지는 체크 함수를 사용하고 있지 않다.

- [ ] 자료조사: 시스템 디스크립터 외에 어플리케이션에서 파일 오픈 시에 시작하는 디스크립터의 번호를 알자.

        고민스러운 부분이다.
        스트림 처리를 해야 하는데, 사용자가, 스트림 객체를 고민없이 사용하도록 하고 싶다.
        그렇지만 여기에는 어디에서 스트림이 존재하지 않는다.
        디스크립터는 스트림을 가지고 있지 않기 때문이다.
        설계의 통일성을 가지면서 스트림을 사용해서 읽기를 수행했을 때, 스트림의 최적화를 이룰 수 있는 방법이 있을까?
        PREPROCESSOR 뿐인가?
        디스크립터 ON 을 넣어 두었는데, 여기에 두면 되겠구나....
        소켓의 경우, xsocketon (descriptor, xdescriptoreventtype_in, buffer, n);

- [ ] 리팩토링 할 시점이구나.
- [ ] XCLIENT SUBSCRIBER
- [ ] MAP ADD 시에 이전 값을 가지고 올 수 있도록 했는데, 버그가 있어 보인다.
- [ ] IPv6 지원 ...
- [ ] 로고 - EVA
- [ ] FUNCTION TRACE 를 구현하자. (로그 모듈에 넣고,)

        스택을 구현했다는 것은 이럴 때 사용할만 하구만,....

- [ ] 맵의 TRAVERSE 를 구현해야겠다.
- [ ] 간단한 트위터 커맨드 라인 인터페이스
- [ ] ATEXIT 적용하기
- [ ] HASH
- [ ] B+ TREE
- [ ] TODO: ENGINE NODE OR GENERATOR NODE ... 세션 풀을 등록해서 사용할 수 있도록 하자. 다만, ... 
- [ ] xserver 구조체의 session 멤버를 세션 풀로 다시 만들자. 그리고 사용자가 커스터마이징할 수 있도록 하자.
- [ ] 클라이언트 풀을 만들고 동작 테스트를 진행하자.
- [ ] 자동으로 테스트할 수 있는 방법을 알아보자.
- [ ] 에코 테스트를 진행할때, 큰 파일을 여러 소켓을 이용해서 전송하는 프로그램을 만들어서 진행하자.
- [ ] 제로 카피는 마스크로 제공하자. (엔진의 프로세스에서 제로 카피 마스크가 존재하면, WRITE, READ, WRITE 로직을 READ 수행 시에 WRITE 를 하도록 하자. SEND FILE 을 수행할 수 있도록 하자.)
- [ ] 이벤트 타입과 디스크립터 상태 상수를 정리하자.
- [ ] 콘솔 I/O 에서 OUT FLUSH 의 경우 - WRITE 를 수행하고
- [ ] WRITE 버퍼가 더 이상 존재하지 않을 경우
- [ ] OUT FLUSH 상태에서만 OUT 이 발생할 수 있도록 하자.
- [ ] 클라이언트 풀은 엔진에 등록되는 객체는 맞는 것 같다. (특히나,... )
- [ ] 문서를 정리할 때이다.
- [ ] STRING 관련 함수를 만들자.
- [ ] 정규 표현식 관련하여 POSIX 를 대체할만한 무엇인가를 만들자.

----

1 - 1024 까지 데이터를 삽입하고, ...

LEAF NODE'S 의 수행 시간을 체크해보자.

- [x] DICTIONARY'S VALIDATE

----

콜백을 이용한 자료 구조

- [x] LIST
- [x] MAP
- [x] SET
- [x] ARRAY
- [x] STACK
- [x] QUEUE

원격 자료구조

----

- [x] EVA PACKAGE 를 만들자. - 고민스러움
- [x] 콘솔은 이벤트 타겟일까? 현재 구현에서는 콘솔은 이벤트 타겟이 아니다.

        두개의 이벤트 타겟을 관리하는 이벤트 객체와 전혀 상관 없는 객체이다.
        하지만 REGISTER 가 발생한다면, 동일한 객체를 넣고 싶다.
        클라이언트 풀도 마찬가지이다. 과연 관계를 가지도록 하는 것이 좋은 것일까?
        동일하게 처리되도록 한다면 동일한 처리가 가능하고,
        앞으로 유사한 것들을 같은 동일한 로직으로 가지고 갈 수 있다.
        하지만, 그렇지 않다면, 로직은 간결하고 특수화를 위한 것들이 더 늘어난 것이다.
        무엇이든 일장일단이 있다.
        콘솔과 클라이언트, 클라이언트 풀은 EVA 에 등록하는 것으로 하자.
        이벤트 타겟이 아닌 것으로

EVA PACKAGE 는 하나의 네트워크 어플리케이션을 만들기 위한 패키지이다.

스크립트 기반으로 테스트를 가능하게 하자.

----

- [x] 콘솔에 EVENT ON 이 존재하지 않아서 SEG FAULT 가 발생한다.
- [x] 메모리 릭 체크를 위해서 콘솔 입출력을 통해서 CLI 를 구현하자.
- [x] 함수에 함수의 입출력에 대한 로그를 삽입하였습니다.
- [x] 로그 함수중에서 FUNCTION START/END 삽입 시에 space padding 을 이용해서 체크하도록 하였습니다.
- [x] 로그 함수중에서 INFINITE 로그가 발생할 경우를 위해서 xdebugonly(code) 를 통해서 출력을 하지 않도록 하였습니다.
- [x] 패딩을 이용해서 로그 타입 문자열의 패딩을 적용할 수 있도록 하자.
- [x] 콘솔 서브스크라이버에 콘솔 디스크립터 파라미터 추가
- [x] 콘솔 아웃 시에 버퍼에만 삽입하고 나머지는 로직에 맞긴다.
- [x] 콘솔에 FLUSH 로직을 적용하자.
- [x] IN FLUSH 의 경우 버퍼를 비우자.
- [x] 스트림 클리어 함수를 만들자.

-----

- [x] 메모리 릭 체크

```
novemberizing@novemberizing-switch:~/Workspace/novemberizing/eva$ sudo valgrind --leak-check=full --show-leak-kinds=all ./src/evad 
==31330== Memcheck, a memory error detector
==31330== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==31330== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==31330== Command: ./src/evad
==31330== 
greeting
eva> Quit
==31330== 
==31330== HEAP SUMMARY:
==31330==     in use at exit: 492 bytes in 12 blocks
==31330==   total heap usage: 475 allocs, 463 frees, 277,962 bytes allocated
==31330== 
==31330== 4 bytes in 1 blocks are still reachable in loss record 1 of 12
==31330==    at 0x483DD99: calloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==31330==    by 0x10B198: xlogout (log.c:132)
==31330==    by 0x113CE0: xconsolesubscriber_set (console.c:87)
==31330==    by 0x10A7CF: main (eva.c:33)
==31330== 
==31330== 16 bytes in 1 blocks are still reachable in loss record 2 of 12
==31330==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==31330==    by 0x10AFE7: xlogpath_set (log.c:90)
==31330==    by 0x10A7B6: main (eva.c:30)
==31330== 
==31330== 16 bytes in 1 blocks are still reachable in loss record 3 of 12
==31330==    at 0x483DD99: calloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==31330==    by 0x10B1C8: xlogout (log.c:135)
==31330==    by 0x113CE0: xconsolesubscriber_set (console.c:87)
==31330==    by 0x10A7CF: main (eva.c:33)
==31330== 
==31330== 32 bytes in 1 blocks are still reachable in loss record 4 of 12
==31330==    at 0x483DD99: calloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==31330==    by 0x119C82: xeventqueue_new (queue.c:26)
==31330==    by 0x10D712: xeventengine_new (engine.c:27)
==31330==    by 0x10A7D4: main (eva.c:34)
==31330== 
==31330== 32 bytes in 1 blocks are still reachable in loss record 5 of 12
==31330==    at 0x483DD99: calloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==31330==    by 0x119C82: xeventqueue_new (queue.c:26)
==31330==    by 0x10D71F: xeventengine_new (engine.c:28)
==31330==    by 0x10A7D4: main (eva.c:34)
==31330== 
==31330== 32 bytes in 1 blocks are still reachable in loss record 6 of 12
==31330==    at 0x483DD99: calloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==31330==    by 0x11359B: xdescriptoreventgeneratorsubscriptionlist_new (list.c:23)
==31330==    by 0x11237A: xdescriptoreventgenerator_new (epoll.c:266)
==31330==    by 0x10D733: xeventengine_new (engine.c:30)
==31330==    by 0x10A7D4: main (eva.c:34)
==31330== 
==31330== 32 bytes in 1 blocks are still reachable in loss record 7 of 12
==31330==    at 0x483DD99: calloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==31330==    by 0x11359B: xdescriptoreventgeneratorsubscriptionlist_new (list.c:23)
==31330==    by 0x112386: xdescriptoreventgenerator_new (epoll.c:267)
==31330==    by 0x10D733: xeventengine_new (engine.c:30)
==31330==    by 0x10A7D4: main (eva.c:34)
==31330== 
==31330== 48 bytes in 1 blocks are still reachable in loss record 8 of 12
==31330==    at 0x483DD99: calloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==31330==    by 0x112371: xdescriptoreventgenerator_new (epoll.c:264)
==31330==    by 0x10D733: xeventengine_new (engine.c:30)
==31330==    by 0x10A7D4: main (eva.c:34)
==31330== 
==31330== 64 bytes in 1 blocks are still reachable in loss record 9 of 12
==31330==    at 0x483DD99: calloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==31330==    by 0x11A9D2: xeventsubscription_new (subscription.c:17)
==31330==    by 0x10DF71: xeventengine_server_register (engine.c:168)
==31330==    by 0x10A7FA: main (eva.c:36)
==31330== 
==31330== 64 bytes in 1 blocks are still reachable in loss record 10 of 12
==31330==    at 0x483DD99: calloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==31330==    by 0x11A9D2: xeventsubscription_new (subscription.c:17)
==31330==    by 0x10E16D: xeventengine_descriptor_register (engine.c:195)
==31330==    by 0x10A814: main (eva.c:37)
==31330== 
==31330== 64 bytes in 1 blocks are still reachable in loss record 11 of 12
==31330==    at 0x483DD99: calloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==31330==    by 0x11A9D2: xeventsubscription_new (subscription.c:17)
==31330==    by 0x10E16D: xeventengine_descriptor_register (engine.c:195)
==31330==    by 0x10A82E: main (eva.c:38)
==31330== 
==31330== 88 bytes in 1 blocks are still reachable in loss record 12 of 12
==31330==    at 0x483DD99: calloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==31330==    by 0x10D709: xeventengine_new (engine.c:25)
==31330==    by 0x10A7D4: main (eva.c:34)
==31330== 
==31330== LEAK SUMMARY:
==31330==    definitely lost: 0 bytes in 0 blocks
==31330==    indirectly lost: 0 bytes in 0 blocks
==31330==      possibly lost: 0 bytes in 0 blocks
==31330==    still reachable: 492 bytes in 12 blocks
==31330==         suppressed: 0 bytes in 0 blocks
==31330== 
==31330== For lists of detected and suppressed errors, rerun with: -s
==31330== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

----

1. LEAK = 

```
==31330== 4 bytes in 1 blocks are still reachable in loss record 1 of 12
==31330==    at 0x483DD99: calloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==31330==    by 0x10B198: xlogout (log.c:132)
==31330==    by 0x113CE0: xconsolesubscriber_set (console.c:87)
==31330==    by 0x10A7CF: main (eva.c:33)
```


2. LEAK

```
==32468== 16 bytes in 1 blocks are still reachable in loss record 1 of 11
==32468==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==32468==    by 0x10AFEC: xlogpath_set (log.c:90)
==32468==    by 0x10A7B6: main (eva.c:30)
```

3. LEAK

```
==37270== 32 bytes in 1 blocks are still reachable in loss record 1 of 9
==37270==    at 0x483DD99: calloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==37270==    by 0x119D19: xeventqueue_new (queue.c:26)
==37270==    by 0x10D7A9: xeventengine_new (engine.c:27)
==37270==    by 0x10A7D4: main (eva.c:34)
```

==38351== Conditional jump or move depends on uninitialised value(s)
==38351==    at 0x48FBC02: __vfprintf_internal (vfprintf-internal.c:1687)
==38351==    by 0x10B575: xlogout (log.c:224)
==38351==    by 0x1136D0: xdescriptoreventgeneratorsubscriptionlist_new (list.c:27)
==38351==    by 0x112441: xdescriptoreventgenerator_new (epoll.c:266)
==38351==    by 0x10D7CA: xeventengine_new (engine.c:30)
==38351==    by 0x10A7D4: main (eva.c:34)
==38351== 
==38351== Conditional jump or move depends on uninitialised value(s)
==38351==    at 0x48FBC02: __vfprintf_internal (vfprintf-internal.c:1687)
==38351==    by 0x10B575: xlogout (log.c:224)
==38351==    by 0x1136D0: xdescriptoreventgeneratorsubscriptionlist_new (list.c:27)
==38351==    by 0x11244D: xdescriptoreventgenerator_new (epoll.c:267)
==38351==    by 0x10D7CA: xeventengine_new (engine.c:30)
==38351==    by 0x10A7D4: main (eva.c:34)
==38351== 
==38351== Use of uninitialised value of size 8
==38351==    at 0x48DF81B: _itoa_word (_itoa.c:179)
==38351==    by 0x48FB6F4: __vfprintf_internal (vfprintf-internal.c:1687)
==38351==    by 0x10B575: xlogout (log.c:224)
==38351==    by 0x116460: xserversocket_new (socket.c:25)
==38351==    by 0x116026: xservernew (server.c:17)
==38351==    by 0x10AC63: evaechoserver_get (echo.c:45)
==38351==    by 0x10A7E5: main (eva.c:36)
==38351== 
==38351== Conditional jump or move depends on uninitialised value(s)
==38351==    at 0x48DF82D: _itoa_word (_itoa.c:179)
==38351==    by 0x48FB6F4: __vfprintf_internal (vfprintf-internal.c:1687)
==38351==    by 0x10B575: xlogout (log.c:224)
==38351==    by 0x116460: xserversocket_new (socket.c:25)
==38351==    by 0x116026: xservernew (server.c:17)
==38351==    by 0x10AC63: evaechoserver_get (echo.c:45)
==38351==    by 0x10A7E5: main (eva.c:36)
==38351== 
==38351== Conditional jump or move depends on uninitialised value(s)
==38351==    at 0x48FC3A8: __vfprintf_internal (vfprintf-internal.c:1687)
==38351==    by 0x10B575: xlogout (log.c:224)
==38351==    by 0x116460: xserversocket_new (socket.c:25)
==38351==    by 0x116026: xservernew (server.c:17)
==38351==    by 0x10AC63: evaechoserver_get (echo.c:45)
==38351==    by 0x10A7E5: main (eva.c:36)
==38351== 
==38351== Conditional jump or move depends on uninitialised value(s)
==38351==    at 0x48FB86E: __vfprintf_internal (vfprintf-internal.c:1687)
==38351==    by 0x10B575: xlogout (log.c:224)
==38351==    by 0x116460: xserversocket_new (socket.c:25)
==38351==    by 0x116026: xservernew (server.c:17)
==38351==    by 0x10AC63: evaechoserver_get (echo.c:45)
==38351==    by 0x10A7E5: main (eva.c:36)
==38351== 
==38351== Conditional jump or move depends on uninitialised value(s)
==38351==    at 0x483EF58: strlen (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==38351==    by 0x48FCE94: __vfprintf_internal (vfprintf-internal.c:1688)
==38351==    by 0x10B575: xlogout (log.c:224)
==38351==    by 0x10C0CB: xstreamfront (stream.c:127)
==38351==    by 0x115A6E: xconsoleout_flush (console.c:545)
==38351==    by 0x10AA92: evacli (console.c:42)
==38351==    by 0x114D0A: xconsoledescriptorsubscriber_input (console.c:340)
==38351==    by 0x112783: xdescriptoreventgenerator_register (epoll.c:323)
==38351==    by 0x10E25F: xeventengine_descriptor_register (engine.c:202)
==38351==    by 0x10A82E: main (eva.c:38)
==38351== 
==38351== Conditional jump or move depends on uninitialised value(s)
==38351==    at 0x48FBC02: __vfprintf_internal (vfprintf-internal.c:1687)
==38351==    by 0x10B575: xlogout (log.c:224)
==38351==    by 0x10C0CB: xstreamfront (stream.c:127)
==38351==    by 0x115A6E: xconsoleout_flush (console.c:545)
==38351==    by 0x10AA92: evacli (console.c:42)
==38351==    by 0x114D0A: xconsoledescriptorsubscriber_input (console.c:340)
==38351==    by 0x112783: xdescriptoreventgenerator_register (epoll.c:323)
==38351==    by 0x10E25F: xeventengine_descriptor_register (engine.c:202)
==38351==    by 0x10A82E: main (eva.c:38)
==38351== 
==38351== Use of uninitialised value of size 8
==38351==    at 0x48DF7BA: _itoa_word (_itoa.c:180)
==38351==    by 0x48FB6F4: __vfprintf_internal (vfprintf-internal.c:1687)
==38351==    by 0x10B575: xlogout (log.c:224)
==38351==    by 0x10C0CB: xstreamfront (stream.c:127)
==38351==    by 0x115A6E: xconsoleout_flush (console.c:545)
==38351==    by 0x10AA92: evacli (console.c:42)
==38351==    by 0x114D0A: xconsoledescriptorsubscriber_input (console.c:340)
==38351==    by 0x112783: xdescriptoreventgenerator_register (epoll.c:323)
==38351==    by 0x10E25F: xeventengine_descriptor_register (engine.c:202)
==38351==    by 0x10A82E: main (eva.c:38)
==38351== 
==38351== Conditional jump or move depends on uninitialised value(s)
==38351==    at 0x48DF7CC: _itoa_word (_itoa.c:180)
==38351==    by 0x48FB6F4: __vfprintf_internal (vfprintf-internal.c:1687)
==38351==    by 0x10B575: xlogout (log.c:224)
==38351==    by 0x10C0CB: xstreamfront (stream.c:127)
==38351==    by 0x115A6E: xconsoleout_flush (console.c:545)
==38351==    by 0x10AA92: evacli (console.c:42)
==38351==    by 0x114D0A: xconsoledescriptorsubscriber_input (console.c:340)
==38351==    by 0x112783: xdescriptoreventgenerator_register (epoll.c:323)
==38351==    by 0x10E25F: xeventengine_descriptor_register (engine.c:202)
==38351==    by 0x10A82E: main (eva.c:38)
==38351== 
==38351== Conditional jump or move depends on uninitialised value(s)
==38351==    at 0x48FC3A8: __vfprintf_internal (vfprintf-internal.c:1687)
==38351==    by 0x10B575: xlogout (log.c:224)
==38351==    by 0x10C0CB: xstreamfront (stream.c:127)
==38351==    by 0x115A6E: xconsoleout_flush (console.c:545)
==38351==    by 0x10AA92: evacli (console.c:42)
==38351==    by 0x114D0A: xconsoledescriptorsubscriber_input (console.c:340)
==38351==    by 0x112783: xdescriptoreventgenerator_register (epoll.c:323)
==38351==    by 0x10E25F: xeventengine_descriptor_register (engine.c:202)
==38351==    by 0x10A82E: main (eva.c:38)
==38351== 
==38351== Conditional jump or move depends on uninitialised value(s)
==38351==    at 0x48FB86E: __vfprintf_internal (vfprintf-internal.c:1687)
==38351==    by 0x10B575: xlogout (log.c:224)
==38351==    by 0x10C0CB: xstreamfront (stream.c:127)
==38351==    by 0x115A6E: xconsoleout_flush (console.c:545)
==38351==    by 0x10AA92: evacli (console.c:42)
==38351==    by 0x114D0A: xconsoledescriptorsubscriber_input (console.c:340)
==38351==    by 0x112783: xdescriptoreventgenerator_register (epoll.c:323)
==38351==    by 0x10E25F: xeventengine_descriptor_register (engine.c:202)
==38351==    by 0x10A82E: main (eva.c:38)




==39156== Use of uninitialised value of size 8
==39156==    at 0x48DF81B: _itoa_word (_itoa.c:179)
==39156==    by 0x48FB6F4: __vfprintf_internal (vfprintf-internal.c:1687)
==39156==    by 0x10B575: xlogout (log.c:224)
==39156==    by 0x11646B: xserversocket_new (socket.c:25)
==39156==    by 0x116031: xservernew (server.c:17)
==39156==    by 0x10AC63: evaechoserver_get (echo.c:45)
==39156==    by 0x10A7E5: main (eva.c:36)