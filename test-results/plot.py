import matplotlib.pyplot as plt

# Plot the results of the test runs
results = [
  ("base", 357.239),
  ("base static auto omp  2", 187.295),
  ("base static auto omp  4", 101.109),
  ("base static auto omp  8", 50.994),
  ("base static auto omp 16", 29.513),
  ("base static 1 omp 16", 33.088),
  ("base dynamic omp 16", 33.072),
  ("remove tmp var permute", 23.482),
  ("BVH", 16.082),
  ("BVH static auto omp  2", 11.854),
  ("BVH static auto omp  4", 8.320),
  ("BVH static auto omp  8", 4.514),
  ("BVH static auto omp 16", 2.790),
  ("precompute invDir intersectAABB", 2.640),
  ("fast_fmax and fast_fmin", 0.499),
  ("early return impl", 0.300)
]

results.sort(key=lambda x: x[1], reverse=True)

# Sort the results by time
plt.figure(figsize=(12, 6))
bars = plt.bar([x[0] for x in results], [x[1] for x in results])
plt.yscale('log')  # Set the y-axis to logarithmic scale
plt.xticks(rotation=30, ha='right')  # Rotate labels and align them to the right
plt.ylim(0, 1000)  # Set the y-axis limits
plt.ylabel("Time (s)")
plt.gcf().subplots_adjust(bottom=0.4)  # Adjust the bottom margin to ensure labels are visible
plt.title("Performance results")

# Display the value of each bar at the top
for bar in bars:
  height = bar.get_height()
  plt.text(bar.get_x() + bar.get_width() / 2, height, f'{height:.3f}', ha='center', va='bottom', fontsize=8)

# Save the plot to an eps file
plt.savefig("results.eps", format='eps', bbox_inches='tight')
plt.show()
