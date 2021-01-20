# Introduction to Dockerfile

Containers initial state are loaded from an *image*.

Use the following command to list the images avaible on your machine.

```
docker images
```

If you have done ex0, you should at least have the ubuntu and the wordpress images.

Images are built layers after layers, you can inspect these layers like this:

```
docker history ubuntu
```

**Dockerfiles** are used to describe how to stack additional layers on top of an existing image to build new images.

# My first dockerfile

Lets build a image that will make the container execute the `hello_world.sh` script.

Complete the `Dockerfile` by adding the following building instructions:

* `COPY hello_world.sh /hello_world.sh` will copy the script into the image.
* `ENTRYPOINT [ "/hello_world.sh" ]` will set the script as the initial running process.

Run `docker build -t my_first_image .` to build your image.

Run a container from this image.

# The `RUN` instruction

Docker can commit the modification of the file system made by a container into a new image. (see `docker diff` and `docker commit` for more details)

The `RUN` instruction of the Dockerfile allows you to run some processes during the build step.

Rewrite the `Dockerfile` to:

1. `COPY` the `hello_world.c`,
2. `RUN` gcc to compile hello_world (remember that without `-o`, gcc will output `a.out`)
3. set hello_world as the `ENTRYPOINT`

Then build and run the resulting container.

The image building procedure can cache intermediate steps if the dependencies did not change.

1. Try to rebuild the same image to see the effect of the cache.
2. Modify hello_world.c to see that the `COPY` instruction detects the modification.
