1. 
```
prompt> ./fork.py -s 10 -c

ARG seed 10
ARG fork_percentage 0.7
ARG actions 5
ARG action_list
ARG show_tree False
ARG just_final False
ARG leaf_only False
ARG local_reparent False
ARG print_style fancy
ARG solve True

                           Process Tree:
                               a

Action: a forks b
                               a
                               └── b
Action: a forks c
                               a
                               ├── b
                               └── c
Action: c EXITS
                               a
                               └── b
Action: a forks d
                               a
                               ├── b
                               └── d
Action: a forks e
                               a
                               ├── b
                               ├── d
                               └── e
```

2. When the fork percentage become larger, the process tree has more branches, more depth and bigger width.

- [Process tree with fork percentage 0.1](./process%20tree%201.md)
- [Process tree with fork percentage 0.9](./process%20tree%202.md)

3. 
```
prompt> ./fork.py -t

ARG seed -1
ARG fork_percentage 0.7
ARG actions 5
ARG action_list
ARG show_tree True
ARG just_final False
ARG leaf_only False
ARG local_reparent False
ARG print_style fancy
ARG solve False

                           Process Tree:
                               a

Action? a forks b
                               a
                               └── b
Action? b EXITS
                               a
Action? a forks c
                               a
                               └── c
Action? a forks d
                               a
                               ├── c
                               └── d
Action? d forks e
                               a
                               ├── c
                               └── d
                                   └── e
```                                   
                            
4. 
When 'c' exits, all children of c, including indirect children of any depth (for example children of children of c), in this case d and e, become the children of their **highest ancestors** in the process tree. In this case, d and e becomes the parent of a, which is their highest ancestor in the process tree.
```
prompt> ./fork.py -A a+b,b+c,c+d,c+e,c- -c

ARG seed -1
ARG fork_percentage 0.7
ARG actions 5
ARG action_list a+b,b+c,c+d,c+e,c-
ARG show_tree False
ARG just_final False
ARG leaf_only False
ARG local_reparent False
ARG print_style fancy
ARG solve False

                           Process Tree:
                               a

Action: a forks b
                               a
                               └── b
Action: b forks c
                               a
                               └── b
                                   └── c
Action: c forks d
                               a
                               └── b
                                   └── c
                                       └── d
Action: c forks e
                               a
                               └── b
                                   └── c
                                       ├── d
                                       └── e
Action: c EXITS
                               a
                               ├── b
                               ├── d
                               └── e
```


More examples:

```
prompt> ./fork.py -A a+b,b+c,c+d,c+e,e+f,c- -c

ARG seed -1
ARG fork_percentage 0.7
ARG actions 5
ARG action_list a+b,b+c,c+d,c+e,e+f,c-
ARG show_tree False
ARG just_final False
ARG leaf_only False
ARG local_reparent False
ARG print_style fancy
ARG solve True

                           Process Tree:
                               a

Action: a forks b
                               a
                               └── b
Action: b forks c
                               a
                               └── b
                                   └── c
Action: c forks d
                               a
                               └── b
                                   └── c
                                       └── d
Action: c forks e
                               a
                               └── b
                                   └── c
                                       ├── d
                                       └── e
Action: e forks f
                               a
                               └── b
                                   └── c
                                       ├── d
                                       └── e
                                           └── f
Action: c EXITS
                               a
                               ├── b
                               ├── d
                               ├── e
                               └── f

d,e,f all becomes 
```

- When using -R flag, orphaned processes become children of their **closest ancestors**.

```
prompt> ./fork.py -A a+b,b+c,c+d,c+e,c- -R -c

ARG seed -1
ARG fork_percentage 0.7
ARG actions 5
ARG action_list a+b,b+c,c+d,c+e,c-
ARG show_tree False
ARG just_final False
ARG leaf_only False
ARG local_reparent True
ARG print_style fancy
ARG solve True

                           Process Tree:
                               a

Action: a forks b
                               a
                               └── b
Action: b forks c
                               a
                               └── b
                                   └── c
Action: c forks d
                               a
                               └── b
                                   └── c
                                       └── d
Action: c forks e
                               a
                               └── b
                                   └── c
                                       ├── d
                                       └── e
Action: c EXITS
                               a
                               └── b
                                   ├── d
                                   └── e
```                                   

More examples:

```
prompt> ./fork.py -A a+b,b+c,c+d,c+e,e+f,c- -c -R

ARG seed -1
ARG fork_percentage 0.7
ARG actions 5
ARG action_list a+b,b+c,c+d,c+e,e+f,c-
ARG show_tree False
ARG just_final False
ARG leaf_only False
ARG local_reparent True
ARG print_style fancy
ARG solve True

                           Process Tree:
                               a

Action: a forks b
                               a
                               └── b
Action: b forks c
                               a
                               └── b
                                   └── c
Action: c forks d
                               a
                               └── b
                                   └── c
                                       └── d
Action: c forks e
                               a
                               └── b
                                   └── c
                                       ├── d
                                       └── e
Action: e forks f
                               a
                               └── b
                                   └── c
                                       ├── d
                                       └── e
                                           └── f
Action: c EXITS
                               a
                               └── b
                                   ├── d
                                   └── e
                                       └── f
```                                       

5. 
```
prompt> ./fork.py -F

ARG seed -1
ARG fork_percentage 0.7
ARG actions 5
ARG action_list
ARG show_tree False
ARG just_final True
ARG leaf_only False
ARG local_reparent False
ARG print_style fancy
ARG solve False

                           Process Tree:
                               a

Action: a forks b               
Action: b forks c
Action: b forks d
Action: c EXITS
Action: d forks e

                        Final Process Tree?

                        a
                        └──b
                            └──d
                                └──e
```

6.
```
prompt> ./fork.py -F -t

ARG seed -1
ARG fork_percentage 0.7
ARG actions 5
ARG action_list
ARG show_tree True
ARG just_final True
ARG leaf_only False
ARG local_reparent False
ARG print_style fancy
ARG solve False

                           Process Tree:
                               a

Action? a forks b
Action? b forks c
Action? b forks d
Action? c forks e
Action? d forks f

                        Final Process Tree:
                               a
                               └── b
                                   ├── c
                                   │   └── e
                                   └── d
                                       └── f
```