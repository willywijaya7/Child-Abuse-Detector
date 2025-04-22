from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/')
def index():
    return "<h1>Hello, World!</h1>"

@app.route('/track', methods=['POST'])
def track():
    data = request.get_json()
    if not data:
        return jsonify({"error": "Invalid JSON"}), 400

    latitude = data.get("latitude")
    longitude = data.get("longitude")

    if latitude is None or longitude is None:
        return jsonify({"error": "Missing latitude or longitude"}), 400

    # You can add database logging or alerting here
    print(f"[INFO] Received coordinates: Latitude={latitude}, Longitude={longitude}")

    return jsonify({
        "status": "success",
        "message": "Coordinates received.",
        "latitude": latitude,
        "longitude": longitude
    }), 200

if __name__ == '__main__':
    app.run(port=5000)
