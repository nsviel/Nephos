# Nephos
## Vulkan-Based Point Cloud Engine

![screenshot](https://github.com/nsviel/Nephos/assets/80487132/711383b1-af32-4600-a0b5-3b0114052698)

## Documentation

<details><summary>Characteristics</summary>

This engine is primarily destined for point cloud visualization, it does not display triangle or line topologies for loaded objects.

A particular work on point cloud visualization shader has been made in this engine with the integration of the EDL shader algorithm presented in the Ph.D. thesis of Christian BOUCHENY.

</details>

<details><summary>Installation</summary>
For now the engine is only supported for Linux OS and was tested on Ubuntu 22.04LTS.

To proceed with the installation, run the script file in the program directory
```
./install.sh
```

Then compile and run the executable
```
 mkdir build && cd build && cmake .. && make -j4 && ./executable
 or
 ./run.sh
```
</details>

<details><summary>License</summary>

 # Creative Commons Attribution-NonCommercial 4.0 International License (CC BY-NC 4.0)

 **You are free to:**

 - **Share**: Copy and redistribute the material in any medium or format.
 - **Adapt**: Remix, transform, and build upon the material.

 **Under the following terms:**

 - **Attribution**: You must give appropriate credit, provide a link to the license, and indicate if changes were made. You may do so in any reasonable manner, but not in any way that suggests the licensor endorses you or your use.
 - **NonCommercial**: You may not use the material for commercial purposes.

 **No additional restrictions:**

 - You may not apply legal terms or technological measures that legally restrict others from doing anything the license permits.

 **Notices:**

 - You do not have to comply with the license for elements of the material in the public domain or where your use is permitted by an applicable exception or limitation.
 - No warranties are given. The license may not give you all the permissions necessary for your intended use. For example, other rights such as publicity, privacy, or moral rights may limit how you use the material.

 For the full legal text, see [CC BY-NC 4.0 License](https://creativecommons.org/licenses/by-nc/4.0/legalcode).

</details>
