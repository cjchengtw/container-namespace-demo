fd = open(argv[1],O_RDONLY);
setns(fd, 0);
execve(argv[2], &argv[2]);
