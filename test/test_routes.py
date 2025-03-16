import pytest
import requests

BASE_URL = "http://localhost:8081"

def test_example_route():
    response = requests.get(f"{BASE_URL}/example")
    print(f"Response from /example: {response.status_code} - {response.text}")
    assert response.status_code == 200
    assert response.text == "Example response"

def test_info_route():
    response = requests.get(f"{BASE_URL}/info")
    print(f"Response from /info: {response.status_code} - {response.text}")
    assert response.status_code == 200
    assert "Client IP" in response.text
    assert "Time" in response.text

'''
def test_capture_route():
    response = requests.get(f"{BASE_URL}/capture")
    print(f"Response from /capture: {response.status_code} - {response.text}")
    assert response.status_code == 200
    assert "Image captured successfully" in response.text or "Failed to capture image" in response.text
'''

'''
def test_file_operation_route():
    # 假设有一个文件路径 /myprojects/Demo/test.txt
    file_path = "/myprojects/Demo/test.txt"
    response = requests.get(f"{BASE_URL}/file?file={file_path}")
    print(f"Response from /file?file={file_path}: {response.status_code} - {response.text}")
    assert response.status_code == 200
    assert "File content" in response.text
'''