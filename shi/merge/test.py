import subprocess
import matplotlib.pyplot as plt

# Step 1: Run the Bash script and capture the output
result = subprocess.run(['bash', 'merge.sh'], stdout=subprocess.PIPE, stderr=subprocess.PIPE)

# Step 2: Check if there was an error in running the script
if result.returncode != 0:
    print(f"Error running script: {result.stderr.decode()}")
else:
    # Step 3: Process the output of the script
    output = result.stdout.decode().strip().split('\n')  # Split the output by lines
    timestamps = []
    worst_values = []
    
    # Step 4: Extract and process the data
    for i in range(0, len(output), 2):  # Iterating over every other line (timestamps)
        timestamp = int(output[i])
        times = output[i + 1].split('ms')[:-1]  # Removing the last empty entry after splitting
        # Convert times to integers, then take the worst (maximum) value
        worst_time = max(int(time) for time in times)
        
        timestamps.append(timestamp)
        worst_values.append(worst_time)
    
    # Step 5: Plot the data using matplotlib
    plt.plot(timestamps, worst_values, marker='o', linestyle='-', color='b')
    plt.xlabel('Timestamp (ms)')
    plt.ylabel('Worst Time (ms)')
    plt.title('Worst Execution Time per Iteration')
    plt.grid(True)
    plt.show()

