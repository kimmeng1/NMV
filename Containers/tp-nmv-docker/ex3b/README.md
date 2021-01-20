# Namespaces

0. Build nsenter
1. Build the bomb image
2. Run the container in background (with the safe option saw in ex2)
3. Use `nsenter` to enter the bomb's UTS namespaces and change its hostname to stop the bomb (Why would `docker exec` fail to change the hostname?)
4. Check if the bomb container exited correctly (`docker ps -a` should return exit 0, `docker logs` should have "Bomb has been defused")

You might want to automate the steps.
