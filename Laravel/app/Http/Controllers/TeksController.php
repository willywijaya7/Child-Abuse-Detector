<?php
namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\Models\Pesan;
use Illuminate\Support\Facades\Log;

class TeksController extends Controller
{
    public function receiveMessage(Request $request)
    {
        // Get the 'pesan' parameter sent by ESP32
        $pesan = $request->input('pesan');

        // Log the received message (optional)
        Log::info("Pesan dari ESP32: " . $pesan);

        // Respond back to ESP32
        return response()->json([
            'status' => 'success',
            'pesan_diterima' => $pesan
        ]);
    }
}