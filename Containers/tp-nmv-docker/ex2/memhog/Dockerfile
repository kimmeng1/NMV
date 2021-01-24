FROM numactl
COPY while.c /while.c
RUN memhog 16G
ENTRYPOINT [ "/while" ]
