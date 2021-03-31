# EVA - EVENT LIB

<img src="https://img.shields.io/badge/C-A8B9CC?style=flat-square&logo=C&logoColor=white" />

<!--<script src="https://cdn.jsdelivr.net/npm/chart.js@2.9.4/dist/Chart.min.js"></script>-->

에바(EVA)는 C 로 구현된 고성능의 네트워크 라이브러리입니다. 

## 성능 측정

간단한 6 바이트의 핑을 주고 받는 벤치마킹을 통하여 측정한 결과입니다. 테스트를 진행한 머신은 Acer Aspire V3-372 노트북이며,
CPU 는 Intel(R) Core(TM) i5-6200U CPU @ 2.30GHz 4 코어입니다. 싱글스레드 환경에서 2,000,000 (2백만건) 트랙잭션을 처리하는데, 걸린 시간은 18.346731777 초이며, 초당 109011.241037887 건의 트랜잭션을 처리하였습니다.


| SECOND       | TOTAL   |
| ------------ | ------- |
|  2.081160663 |  200000 |
|  3.822187722 |  400000 |
|  5.567734740 |  600000 |
|  7.534281985 |  800000 |
|  9.367485799 | 1000000 |
| 11.179510302 | 1200000 |
| 12.927178715 | 1400000 |
| 14.683140203 | 1600000 |
| 16.429950513 | 1800000 |
| 18.346731777 | 2000000 |


![2021/03/31 BENCHMARK RESULT](docs/img/2021-03-31-benchmark-result.png)

<!--
<canvas id="performance-chart"></canvas>

<script>
const data = [
    [ 0.909515391 , 100000 ],
    [ 2.081160663 , 200000 ],
    [ 2.949382455 , 300000 ],
    [ 3.822187722 , 400000 ],
    [ 4.695364761 , 500000 ],
    [ 5.567734740 , 600000 ],
    [ 6.637035238 , 700000 ],
    [ 7.534281985 , 800000 ],
    [ 8.492822478 , 900000 ],
    [ 9.367485799 , 1000000 ],
    [ 10.237602857 , 1100000 ],
    [ 11.179510302 , 1200000 ],
    [ 12.051549841 , 1300000 ],
    [ 12.927178715 , 1400000 ],
    [ 13.805017067 , 1500000 ],
    [ 14.683140203 , 1600000 ],
    [ 15.554987859 , 1700000 ],
    [ 16.429950513 , 1800000 ],
    [ 17.440764149 , 1900000 ],
    [ 18.346731777 , 2000000 ]
];

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
-->

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
