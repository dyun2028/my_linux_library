learning about
Sockets, synchronization, threads, processes, file / file descriptors, C, linux cli, memory / pointers, shared files, build systems, posix, syscalls.
## Rough milestones (~12 weeks core, adjustable)
1. Weeks 1–2: fd/file basics + single-threaded echo server
2. Weeks 3–5: thread pool + mutex/condvar job queue (core sync work)
3. Weeks 6–7: concurrency correctness — races, deadlocks, mutex vs
   semaphore vs atomics comparison
4. Weeks 8–9: shared-file logging/persistence, signal handling
5. Weeks 10–11: epoll/poll scalability, Unix socket control channel
6. Week 12: polish, write-up, stretch goal (CLI client)

## Stretch goal: packaging & distribution (post-core, optional)
- Build a `.deb` package (control file, versioning, dependencies) using
  `dpkg-deb` or `checkinstall`
- Install locally via `sudo dpkg -i` to verify packaging correctness
- Optional: host a minimal personal APT repo (e.g., via GitHub Pages) so
  another machine can `add-apt-repository` + `sudo apt install $MY_PACKAGE`
  for real
- Non-goal: official Debian/Ubuntu archive submission or Launchpad PPA —
  out of scope for this project's size

## Non-goals
- No C++ features, no external frameworks
- No distributed systems / multi-machine scope
- No premature abstraction — one binary, one Makefile, incremental growth
- No official package archive submission (see packaging stretch goal above)




