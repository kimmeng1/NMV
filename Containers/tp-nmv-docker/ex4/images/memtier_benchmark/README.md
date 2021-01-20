memtier_benchmark
=================

memtier_benchmark is a command line utility developed by Redis Labs (formerly Garantia Data Ltd.) for load generation and bechmarking NoSQL key-value databases. It offers the following:

* Support for both Redis and Memcache protocols (text and binary)
* Multi-threaded multi-client execution
* Multiple configuration options, including:
 * Read:Write ratio
 * Random and sequential key name pattern policies
 * Random or ranged key expiration
 * ...and much more

Read more at:

* [A High Throughput Benchmarking Tool for Redis and Memcached](https://redislabs.com/blog/memtier_benchmark-a-high-throughput-benchmarking-tool-for-redis-memcached)
* [Pseudo-Random Data, Gaussian Access Pattern and Range Manipulation](https://redislabs.com/blog/new-in-memtier_benchmark-pseudo-random-data-gaussian-access-pattern-and-range-manipulation)

## Getting Started

### Prerequisites

The following libraries are required for building:

* libevent 2.0.10 or newer.
* libpcre 8.x.

The following tools are required
* autoconf
* automake
* GNU make
* GCC C++ compiler

### CentOS 6.x Prerequisites

On a CentOS 6.4 system, use the following to install prerequisites:
```
# yum install autoconf automake make gcc-c++ 
# yum install pcre-devel zlib-devel libmemcached-devel
```

CentOS 6.4 ships with older versions of libevent, which must be manually built
and installed as follows:

To download, build and install libevent-2.0.21:
```
$ wget https://github.com/downloads/libevent/libevent/libevent-2.0.21-stable.tar.gz
$ tar xfz libevent-2.0.21-stable.tar.gz
$ pushd libevent-2.0.21-stable
$ ./configure
$ make
$ sudo make install
$ popd
```

The above steps will install into /usr/local so it does not confict with the 
distribution-bundled versions.  The last step is to set up the 
PKG_CONFIG_PATH so configure can find the newly installed library.

```
$ export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig:${PKG_CONFIG_PATH}
```

Then proceed to follow the build instructions below.


### Ubuntu 12.x Prerequisites

On recent Ubuntu versions, simply install all prerequisites as follows:

```
# apt-get install build-essential autoconf automake libpcre3-dev libevent-dev pkg-config zlib1g-dev
```


### Building and installing

After downloading the source tree, use standard autoconf/automake commands::

```
$ autoreconf -ivf
$ ./configure
$ make
$ make install
```

## Using Docker

```
$ docker build -t memtier_benchmark .
$ docker run --rm memtier_benchmark --help
```

## Using memtier_benchmark

See the included manpage or run::

```
$ memtier_benchmark --help
```

for command line options.



[![githalytics.com alpha](https://cruel-carlota.pagodabox.com/c1e8ecf15c469fbeb0e4eb12e8436c82 "githalytics.com")](http://githalytics.com/RedisLabs/memtier_benchmark)
