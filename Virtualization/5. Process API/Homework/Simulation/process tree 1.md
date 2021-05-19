```
prompt> ./fork.py -s 10 -a 100 -f 0.1 -c

ARG seed 10
ARG fork_percentage 0.1
ARG actions 100
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
Action: b EXITS
                               a
Action: a forks c
                               a
                               └── c
Action: a forks d
                               a
                               ├── c
                               └── d
Action: c EXITS
                               a
                               └── d
Action: d EXITS
                               a
Action: a forks e
                               a
                               └── e
Action: a forks f
                               a
                               ├── e
                               └── f
Action: e EXITS
                               a
                               └── f
Action: f EXITS
                               a
Action: a forks g
                               a
                               └── g
Action: g EXITS
                               a
Action: a forks h
                               a
                               └── h
Action: h EXITS
                               a
Action: a forks i
                               a
                               └── i
Action: a forks j
                               a
                               ├── i
                               └── j
Action: i EXITS
                               a
                               └── j
Action: j EXITS
                               a
Action: a forks k
                               a
                               └── k
Action: k EXITS
                               a
Action: a forks l
                               a
                               └── l
Action: l EXITS
                               a
Action: a forks m
                               a
                               └── m
Action: m EXITS
                               a
Action: a forks n
                               a
                               └── n
Action: n forks o
                               a
                               └── n
                                   └── o
Action: o EXITS
                               a
                               └── n
Action: n EXITS
                               a
Action: a forks p
                               a
                               └── p
Action: a forks q
                               a
                               ├── p
                               └── q
Action: q EXITS
                               a
                               └── p
Action: a forks r
                               a
                               ├── p
                               └── r
Action: p EXITS
                               a
                               └── r
Action: r EXITS
                               a
Action: a forks s
                               a
                               └── s
Action: s forks t
                               a
                               └── s
                                   └── t
Action: t EXITS
                               a
                               └── s
Action: s forks u
                               a
                               └── s
                                   └── u
Action: u EXITS
                               a
                               └── s
Action: s EXITS
                               a
Action: a forks v
                               a
                               └── v
Action: v EXITS
                               a
Action: a forks w
                               a
                               └── w
Action: w EXITS
                               a
Action: a forks x
                               a
                               └── x
Action: x EXITS
                               a
Action: a forks y
                               a
                               └── y
Action: a forks z
                               a
                               ├── y
                               └── z
Action: y EXITS
                               a
                               └── z
Action: z EXITS
                               a
Action: a forks A
                               a
                               └── A
Action: A EXITS
                               a
Action: a forks B
                               a
                               └── B
Action: B EXITS
                               a
Action: a forks C
                               a
                               └── C
Action: C EXITS
                               a
Action: a forks D
                               a
                               └── D
Action: a forks E
                               a
                               ├── D
                               └── E
Action: E forks F
                               a
                               ├── D
                               └── E
                                   └── F
Action: D EXITS
                               a
                               └── E
                                   └── F
Action: F EXITS
                               a
                               └── E
Action: E forks G
                               a
                               └── E
                                   └── G
Action: G EXITS
                               a
                               └── E
Action: E EXITS
                               a
Action: a forks H
                               a
                               └── H
Action: H forks I
                               a
                               └── H
                                   └── I
Action: I EXITS
                               a
                               └── H
Action: H EXITS
                               a
Action: a forks J
                               a
                               └── J
Action: J EXITS
                               a
Action: a forks K
                               a
                               └── K
Action: K EXITS
                               a
Action: a forks L
                               a
                               └── L
Action: L EXITS
                               a
Action: a forks M
                               a
                               └── M
Action: M EXITS
                               a
Action: a forks N
                               a
                               └── N
Action: N EXITS
                               a
Action: a forks O
                               a
                               └── O
Action: O EXITS
                               a
Action: a forks P
                               a
                               └── P
Action: P EXITS
                               a
Action: a forks Q
                               a
                               └── Q
Action: Q EXITS
                               a
Action: a forks R
                               a
                               └── R
Action: R EXITS
                               a
Action: a forks S
                               a
                               └── S
Action: S EXITS
                               a
Action: a forks T
                               a
                               └── T
Action: T EXITS
                               a
Action: a forks U
                               a
                               └── U
Action: U EXITS
                               a
Action: a forks V
                               a
                               └── V
Action: V EXITS
                               a
Action: a forks W
                               a
                               └── W
Action: W EXITS
                               a
Action: a forks X
                               a
                               └── X
Action: X EXITS
                               a
Action: a forks Y
                               a
                               └── Y
Action: Y EXITS
                               a
```

```
prompt> 
```