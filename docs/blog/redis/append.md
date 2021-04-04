__REDIS COMMAND APPEND__
========================

```sh
append key value
```

| FIELD           | DESCRIPTION                          |
| --------------- | ------------------------------------ |
| Time complexity | O(1)                                 |
| Document        | [](https://redis.io/commands/append) |

The amortized time complexity is O(1) assuming the appended value is small and the already present value is of any size, since the dynamic string library used by redis will double the free space available on every reallocation.

If key already exists and is a string, this command appends the value at the end of the string. If key does not exist it is created and set as an empty string, so append will be similar to set in this special case.



Return value
Integer reply: the length of the string after the append operation.

Examples
redis> EXISTS mykey
(integer) 0
redis> APPEND mykey "Hello"
(integer) 5
redis> APPEND mykey " World"
(integer) 11
redis> GET mykey
"Hello World"
redis> 
Pattern: Time series
The APPEND command can be used to create a very compact representation of a list of fixed-size samples, usually referred as time series. Every time a new sample arrives we can store it using the command

APPEND timeseries "fixed-size sample"
Accessing individual elements in the time series is not hard:

STRLEN can be used in order to obtain the number of samples.
GETRANGE allows for random access of elements. If our time series have associated time information we can easily implement a binary search to get range combining GETRANGE with the Lua scripting engine available in Redis 2.6.
SETRANGE can be used to overwrite an existing time series.
The limitation of this pattern is that we are forced into an append-only mode of operation, there is no way to cut the time series to a given size easily because Redis currently lacks a command able to trim string objects. However the space efficiency of time series stored in this way is remarkable.

Hint: it is possible to switch to a different key based on the current Unix time, in this way it is possible to have just a relatively small amount of samples per key, to avoid dealing with very big keys, and to make this pattern more friendly to be distributed across many Redis instances.

An example sampling the temperature of a sensor using fixed-size strings (using a binary format is better in real implementations).

redis> APPEND ts "0043"
(integer) 4
redis> APPEND ts "0035"
(integer) 8
redis> GETRANGE ts 0 3
"0043"
redis> GETRANGE ts 4 7
"0035"
redis> 