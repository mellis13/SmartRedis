# BSD 2-Clause License
#
# Copyright (c) 2021-2024, Hewlett Packard Enterprise
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice, this
#    list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

import io
import os

import numpy as np
from smartredis import Client

# ----- Tests -----------------------------------------------------------


def test_put_get_bytes(mock_data, context):
    """Test put/get_tensor for 1D numpy arrays"""

    client = Client(None, logger_name=context)

    data = np.random.rand(2, 8, 4, 2, 30)
    bytes = io.BytesIO(data.tobytes())

    client.put_bytes("python_bytes", bytes)

    retrieved_bytes = client.get_bytes("python_bytes")

    assert bytes.getvalue() == retrieved_bytes.getvalue()


def test_bytes_exist(mock_data, context):
    """Test that raw bytes exist in the database
    after a put operation"""

    client = Client(None, logger_name=context)

    data = np.random.rand(2, 8, 4, 2, 30)
    bytes = io.BytesIO(data.tobytes())

    client.put_bytes("python_bytes_exist", bytes)

    assert client.bytes_exists("python_bytes_exist")


def test_poll_bytes(mock_data, context):
    """Test that raw bytes are polled correctly"""

    client = Client(None, logger_name=context)

    assert client.poll_bytes("python_bytes_poll", 0.1, 5) == False

    data = np.random.rand(2, 8, 4, 2, 30)
    bytes = io.BytesIO(data.tobytes())

    client.put_bytes("python_bytes_poll", bytes)

    assert client.bytes_exists("python_bytes_exist")

    assert client.poll_bytes("python_bytes_poll", 0.1, 5) == True


def test_remove_bytes(mock_data, context):
    """Test that raw bytes exist in the database
    after a put operation"""

    client = Client(None, logger_name=context)

    data = np.random.rand(2, 8, 4, 2, 30)
    bytes = io.BytesIO(data.tobytes())

    client.put_bytes("python_bytes_removed", bytes)

    assert client.bytes_exists("python_bytes_removed")

    client.remove_bytes("python_bytes_removed", bytes)

    assert not client.bytes_exists("python_bytes_removed")
