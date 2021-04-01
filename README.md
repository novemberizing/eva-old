# EVA - EVENT LIB

<img src="https://img.shields.io/badge/C-A8B9CC?style=flat-square&logo=C&logoColor=white" />

<script src="https://cdn.jsdelivr.net/npm/chart.js@2.9.4/dist/Chart.min.js"></script>

에바(EVA)는 C 로 구현된 고성능의 네트워크 라이브러리입니다. 

## 성능 측정

간단한 6 바이트의 핑을 주고 받는 벤치마킹을 통하여 측정한 결과입니다. 테스트를 진행한 머신은 Acer Aspire V3-372 노트북이며,
CPU 는 Intel(R) Core(TM) i5-6200U CPU @ 2.30GHz 4 코어입니다. 싱글스레드 환경에서 2,000,000 (2백만건) 트랙잭션을 처리하는데, 걸린 시간은 18.346731777 초이며, 초당 109011.241037887 건의 트랜잭션을 처리하였습니다.

| SECOND       | TOTAL   |
| ------------ | ------- |
|  2.187177305 |  200000 |
|  4.039020540 |  400000 |
|  5.890541373 |  600000 |
|  7.747209592 |  800000 |
|  9.595638718 | 1000000 |
| 12.075148053 | 1200000 |
| 13.931401787 | 1400000 |
| 15.793378680 | 1600000 |
| 17.688611180 | 1800000 |
| 19.540924839 | 2000000 |
| 21.370476228 | 2200000 |
| 23.199086479 | 2400000 |
| 25.042867401 | 2600000 |
| 26.867963482 | 2800000 |
| 28.694509937 | 3000000 |
| 30.516808890 | 3200000 |
| 32.342032479 | 3400000 |
| 34.169689374 | 3600000 |
| 36.023972398 | 3800000 |
| 37.847823001 | 4000000 |

| SECOND       | TOTAL   |
| ------------ | ------- |
|  1.231072571 |  100000 |
|  2.797254843 |  200000 |
|  4.043301667 |  300000 |
|  5.141582957 |  400000 |
|  6.300077801 |  500000 |
|  7.574792263 |  600000 |
|  9.496020241 |  700000 |
| 10.520750648 |  800000 |
| 12.018467291 |  900000 |
| 13.136485551 | 1000000 |
| 14.136675818 | 1100000 |
| 15.347321352 | 1200000 |
| 16.595616134 | 1300000 |
| 17.716966548 | 1400000 |
| 18.971059578 | 1500000 |
| 20.075557406 | 1600000 |
| 21.533724023 | 1700000 |
| 22.626812741 | 1800000 |
| 24.406318757 | 1900000 |
| 25.430707710 | 2000000 |



<!--
![2021/03/31 BENCHMARK RESULT](docs/img/2021-03-31-benchmark-result.png)
-->

<canvas id="performance-chart"></canvas>

<script>
const data = [
    [ 1.231072571 , 100000 ],
    [ 2.797254843 , 200000 ],
    [ 4.043301667 , 300000 ],
    [ 5.141582957 , 400000 ],
    [ 6.300077801 , 500000 ],
    [ 7.574792263 , 600000 ],
    [ 9.496020241 , 700000 ],
    [ 10.520750648 , 800000 ],
    [ 12.018467291 , 900000 ],
    [ 13.136485551 , 1000000 ],
    [ 14.136675818 , 1100000 ],
    [ 15.347321352 , 1200000 ],
    [ 16.595616134 , 1300000 ],
    [ 17.716966548 , 1400000 ],
    [ 18.971059578 , 1500000 ],
    [ 20.075557406 , 1600000 ],
    [ 21.533724023 , 1700000 ],
    [ 22.626812741 , 1800000 ],
    [ 24.406318757 , 1900000 ],
    [ 25.430707710 , 2000000 ]
];

// const data = [
//     [ 2.187177305,  200000],
//     [ 4.039020540,  400000],
//     [ 5.890541373,  600000],
//     [ 7.747209592,  800000],
//     [ 9.595638718, 1000000],
//     [12.075148053, 1200000],
//     [13.931401787, 1400000],
//     [15.793378680, 1600000],
//     [17.688611180, 1800000],
//     [19.540924839, 2000000],
//     [21.370476228, 2200000],
//     [23.199086479, 2400000],
//     [25.042867401, 2600000],
//     [26.867963482, 2800000],
//     [28.694509937, 3000000],
//     [30.516808890, 3200000],
//     [32.342032479, 3400000],
//     [34.169689374, 3600000],
//     [36.023972398, 3800000],
//     [37.847823001, 4000000]
// ];

const transaction = data.map(o => o[1] / o[0]);
const label = data.map((o, index) => index + 1);

const chart = new Chart(document.getElementById("performance-chart"), {
    type: "line",
    data: {
        labels: label,
        datasets: [
            {
                label: "Transaction per second",
                data: transaction,
                fill: false,
                borderColor: "rbg(75, 192, 192)",
                lineTension: 0.1
            }
        ],
    },
    options: {
        scales: {
            yAxes: [{
                ticks: {
                    min: 0,
                    max: 120000,
                    fontSize: 14,
                }
            }]
        }
    }
})

</script>


## 로드맵

EVA 는 쉽게 고성능의 서버나 혹은 다중 클라이언트 어플리케이션을 쉽게 작성할 수 있는 라이브러리를 만드는 것이 목표입니다.
버전 0.0.1 은 TCP 에코 서버와 클라이언트를 20 줄 미만의 핸들러와 20줄 미만의 메인 함수를 정의하여 구현할 수 있습니다.

궁극적으로 이벤트 라이브러리를 만드는 것이 목적이며, 이 라이브러리를 통하여 쉽게 고성능의 네트워크 어플리케이션을 쉽게 만들 수 있도록 하려 합니다. 버전 0.0.1 은 리눅스 환경에서 동작하도록 하였고, 버전 1.0.0 은 UDP, 시그널, 잘 알려진 어플리케이션 프로토콜에 대한 지원 등을 계획하고 있습니다. 또한, 싱글 스레드 뿐만이 아닌 멀티 스레드를 지원하여 헤비한 작업의 경우에도 고성능을 보장하는 것이 쉽도록 구현할 것 입니다. 그 외에 UDP 기반으로 분산 네트워크 처리를 쉽게 할 수 있도록 하려 합니다.

## 빌드방법

```sh
$ ./configure
$ make
$ sudo make install
```

## 레디스 벤치 마킹 결과

```
$ redis-benchmark -t set -n 4000000
====== SET ======
  4000000 requests completed in 49.51 seconds
  50 parallel clients
  3 bytes payload
  keep alive: 1

99.45% <= 1 milliseconds
99.98% <= 2 milliseconds
99.99% <= 3 milliseconds
100.00% <= 4 milliseconds
100.00% <= 5 milliseconds
100.00% <= 5 milliseconds
80793.39 requests per second
```
