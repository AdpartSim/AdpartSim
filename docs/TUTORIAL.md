# TUTORIAL

The sample configuration file is located in the `example/` path, which is mainly divided into four modules: **Strategy**, **Node**, **Switche**, and **Network**. The following sections will introduce the different parameter configuration requirements for these four modules.

## Strategy

- **Type** `enum`
- **Epoch** `uint`
- **Workload** `string`

## Node

- **Count ** `uint`
- **Accelerator**
  - **Type** `enum`
  - **Latency_ns** `uint`
  - **ClockFreq_GHz** `double`
  - **Performance_TFLOPS** `double`
- **Communicator**
  - **BufferSize_MB** `double`
  - **Algorithm** `enum`
  - **ReceiveTimeout_s** `double`
- **Memory**
  - **Bandwidth_Gbps** `double`
  - **Latency_ns** `uint`
  - **Capacity_GB** `double`

## Switch

- **Count** `uint`

## Network

It is an array, where each element represents a layer of the network. The configuration parameters for this layer of the network are explained as follows:

- **Type** `enum`
- **Topology** `enum`
- **TopologyAttrs** `list(uint)`
- **NodeCount** `uint`
- **SwitchCount** `uint`
- **RepeatCount** `uint`
- **Bandwidth_Gbps** `double`
- **Latency_ns** `uint`

