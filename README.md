## Implementation of Cuckoo Hashing in FQ-CoDeL in Linux kernel

### Introduction
- This project aims to implement cuckoo hashing scheme for sch_fq_codel in Linux kernel
- Currently we are developing on top of v5.3. Later we will implement it on top of `davem/net-next`

### Project Structure
- The project has following directories:
    - `fq_codel`: This contains the primitive implementations of sch_fq_codel. These are first tries and might now be functional, but can be used as reference for the ideas that came up for implementation
    - `net/sched`: This is the replica of net/sched directory of the kernel source tree. This directory has 4 files
        - `sch_fq_codel.c` : The original v5.3 version of fq_codel
        - `sch_fq_codel_commented.c`: This is the original v5.3 version of fq_codel along with `printk` statements for seeing the internal working on `dmesg`
        - `sch_fq_codel_cuckoo_naive.c`: This is the naive implementation of fq_codel with a hashtable of indexes(a kind of indirection) but uses linear scan on flow table to get the next empty flow
        - `sch_fq_codel_cuckoo_bitmask.c`: This is the `supposedly` optimized version of the `naive` implementation, as it uses a bitmask over a linear scan for getting the next empty flow
    - `testbed`: Contains the scripts for creating a virtual topology using network namespaces to test the qdisc
    - `validation`: Contains .c files for testing various components and functions of the code.
    - `hash_impl`: A reference implementation of hashing functions and schemes used in the project in generic C

### Wiki
- The wiki of this project contains various pages including the `Timeline` that contains the updates and progress of the project
- The wiki contains articles we have written as a part of the project as we learnt various topics

### Contributors
- Main guide: Dr. Mohit P. Tahiliani
- Project mentors: Leslie Monis and Gautam R.
- Members: Nisarg S. Joshi, Yash M. Agarwal, Shweta H. Iyer
