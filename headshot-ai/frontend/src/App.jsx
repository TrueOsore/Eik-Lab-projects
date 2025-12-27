import React, { useState } from 'react'

export default function App() {
  const [file, setFile] = useState(null)
  const [style, setStyle] = useState('corporate')
  const [result, setResult] = useState(null)
  const [loading, setLoading] = useState(false)

  const handleSubmit = async () => {
    if (!file) return
    setLoading(true)

    const formData = new FormData()
    formData.append('image', file)
    formData.append('style', style)

    try {
      const res = await fetch('http://localhost:5000/api/generate-headshot', {
        method: 'POST',
        body: formData
      })
      const data = await res.json()
      setResult(data)
    } catch (err) {
      console.error('Error generating headshot:', err)
      alert('Failed to generate headshot')
    }

    setLoading(false)
  }

  return (
    <div className="max-w-5xl mx-auto px-6 py-10 space-y-8">
      <header className="space-y-2 text-center">
        <h1 className="text-3xl font-bold">Professional Headshot AI</h1>
        <p className="text-gray-600">Upload a photo, choose a style, and generate a professional headshot.</p>
      </header>

      <div className="bg-white p-8 rounded-2xl shadow space-y-6">
        <div className="space-y-2">
          <label className="block text-sm font-medium text-gray-700">Upload photo</label>
          <input
            type="file"
            accept="image/*"
            onChange={(e) => setFile(e.target.files[0])}
            className="block w-full text-sm file:mr-4 file:py-2 file:px-4 file:rounded-lg file:border-0 file:text-sm file:font-semibold file:bg-gray-100 file:text-gray-700 hover:file:bg-gray-200"
          />
        </div>

        <div className="space-y-2">
          <label className="block text-sm font-medium text-gray-700">Select style</label>
          <div className="grid grid-cols-1 sm:grid-cols-3 gap-4">
            {['corporate', 'creative', 'executive'].map((s) => (
              <label
                key={s}
                className={`cursor-pointer rounded-xl border p-4 text-center capitalize
                  ${style === s ? 'border-black bg-gray-50' : 'border-gray-200 hover:border-gray-300'}`}
              >
                <input
                  type="radio"
                  value={s}
                  checked={style === s}
                  onChange={() => setStyle(s)}
                  className="hidden"
                />
                <span className="font-medium">{s}</span>
              </label>
            ))}
          </div>
        </div>

        <div className="pt-4">
          <button
            onClick={handleSubmit}
            disabled={loading}
            className="w-full sm:w-auto bg-black text-white px-6 py-3 rounded-xl font-medium hover:bg-gray-900 disabled:opacity-50"
          >
            {loading ? 'Generating...' : 'Generate Headshot'}
          </button>
        </div>
      </div>

      {result && (
        <div className="grid grid-cols-1 md:grid-cols-2 gap-8">
          <div className="space-y-2">
            <h2 className="font-semibold">Original</h2>
            <img src={`data:image/jpeg;base64,${result.originalImage}`} className="rounded-xl" />
          </div>
          <div className="space-y-2">
            <h2 className="font-semibold">Generated</h2>
            <img src={`data:image/jpeg;base64,${result.generatedImage}`} className="rounded-xl" />
          </div>
        </div>
      )}
    </div>
  )
}
