<!DOCTYPE html>
<html>
<head>
    <title>Daftar Pesan dari ESP32</title>
    <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0/dist/css/bootstrap.min.css">
</head>
<body class="p-4">
    <div class="container">
        <h1>Pesan dari ESP32</h1>
        <table class="table table-bordered mt-4">
            <thead>
                <tr>
                    <th>#</th>
                    <th>Isi Pesan</th>
                    <th>Waktu Diterima</th>
                </tr>
            </thead>
            <tbody>
                @foreach($semuaPesan as $pesan)
                <tr>
                    <td>{{ $loop->iteration }}</td>
                    <td>{{ $pesan->isi }}</td>
                    <td>{{ $pesan->created_at->format('d-m-Y H:i:s') }}</td>
                </tr>
                @endforeach
            </tbody>
        </table>
    </div>
</body>
</html>
