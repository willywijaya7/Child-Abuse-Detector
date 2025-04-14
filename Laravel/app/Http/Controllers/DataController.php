<?php

namespace App\Http\Controllers;

use App\Models\Data;
use Illuminate\Http\Request;

class DataController extends Controller
{
    function index()
    {
        $data = Data::all();
        return $data;
    }

    public function store(Request $request)
    {
        $data = Data::create([
            'data' => $request->input('data')
        ]);

        if ($data) {
            return response()->json(['message' => 'berhasil']);
        } else {
            return response()->json(['message' => 'gagal'], 500);
        }
    }
}
