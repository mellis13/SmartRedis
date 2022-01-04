from smartredis import Client
import numpy as np

client = Client(None, False)

tensor = np.random.randint(-10, 10, size=(2,4))

client.put_tensor("python_docker_tensor", tensor)
