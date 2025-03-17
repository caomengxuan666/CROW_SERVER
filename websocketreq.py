import websocket
import threading
import time
import json

def on_message(ws, message):
    print(f"Received from {ws.url}: {message}")

def on_error(ws, error):
    print(f"Error from {ws.url}: {error}")

def on_close(ws, close_status_code, close_msg):
    print(f"Connection closed from {ws.url}")

def on_open(ws):
    print(f"Connection opened to {ws.url}")
    # 发送拍照请求
    ws.send(json.dumps({"action": "capture"}))
    # 发送录制请求
    ws.send(json.dumps({"action": "record", "command": "start"}))
    time.sleep(5)  # 模拟录制持续时间
    ws.send(json.dumps({"action": "record", "command": "stop"}))

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
    urls = ["ws://127.0.0.1:8081/video"] * 1  # 1000个相同的 URL 示例
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