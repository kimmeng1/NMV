# What is a container?

A container contains! It's as simple as that.

# How are they implemented?

Technically its a [Operating-system-level virtualization](https://en.wikipedia.org/wiki/Operating-system-level_virtualization).

Let look at how Linux does this.

## Namespaces

* `man namespaces`
* `man setns`

## Cgroups

* `/sys/fs/cgroup`

# Can I break out of a container?

Yes, containers are vulnerable.

* http://cve.mitre.org/cgi-bin/cvekey.cgi?keyword=docker
* https://github.com/docker/docker-bench-security
