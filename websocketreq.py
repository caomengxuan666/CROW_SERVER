import websocket
import threading
import time
import json

# commandHandlers 列表，新增 setParam 请求
commandHandlers = [
    {"action": "capture"},
    {"action": "record", "command": "start"},
    {"action": "record", "command": "stop"},
    # 新增 setParam 请求示例
    {"action": "setParam", "paramType": "PIXEL_FORMAT", "paramValue": 1},
    {"action": "setParam", "paramType": "ADJUST_LIGHT", "paramValue": {"auto_moudulate": True, "luminance": 50, "contrast": 30}},
    {"action": "setParam", "paramType": "PALETTE", "paramValue": 2},
    {"action": "setParam", "paramType": "ELECTRONIC_ZOOM", "paramValue": 3},
    {"action": "setParam", "paramType": "SHUTTER_CONTROL", "paramValue": 1},
    {"action": "setParam", "paramType": "CALC_PARAMETER", "paramValue": {
        "emiss": 0.95, "distance": 10.0, "humidity": 50, "backTemp": 25.0,
        "backFlag": 1, "B": 0.1, "KF": 1, "transmittance": 0.8, "coef0": 1, "coef1": 2
    }},
    {"action": "setParam", "paramType": "DEVICE_PORT", "paramValue": [1, 8080]},
    {"action": "setParam", "paramType": "ALARM_INFO", "paramValue": {"state": 1, "highLimit": 100, "lowLimit": 0, "mode": 2}}
]

def on_message(ws, message):
    print(f"Received from {ws.url}: {message}")

def on_error(ws, error):
    print(f"Error from {ws.url}: {error}")

def on_close(ws, close_status_code, close_msg):
    print(f"Connection closed from {ws.url}")

def on_open(ws):
    print(f"Connection opened to {ws.url}")
    # 发送 commandHandlers 中定义的请求
    for command in commandHandlers:
        ws.send(json.dumps(command))
        time.sleep(1)  # 模拟请求间隔

def start_client(url):
    ws = websocket.WebSocketApp(
        url,
        on_message=on_message,
        on_error=on_error,
        on_close=on_close
    )
    ws.on_open = on_open
    ws.run_forever()

if __name__ == "__main__":
    urls = ["ws://127.0.0.1:8081/video"] * 1  # n个相同的 URL 示例
    threads = []
    delay_interval = 0.02  # 20毫秒的延迟

    for i, url in enumerate(urls):
        thread = threading.Thread(target=start_client, args=(url,))
        threads.append(thread)
        thread.start()

        # 每五个请求后延迟20毫秒
        if (i + 1) % 5 == 0:
            time.sleep(delay_interval)

    for thread in threads:
        thread.join()