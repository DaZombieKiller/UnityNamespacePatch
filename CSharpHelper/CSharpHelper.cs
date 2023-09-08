using System.Runtime.InteropServices;
using Microsoft.CodeAnalysis.CSharp;
using Microsoft.CodeAnalysis.Text;

/// <summary>Provides helpers for parsing C# source code.</summary>
public static unsafe class CSharpHelper
{
    /// <summary>Given some C# source text and a type name, determines the namespace of the type.</summary>
    [UnmanagedCallersOnly(EntryPoint = nameof(GetClassNamespace))]
    public static int GetClassNamespace(byte* pText, int textLength, byte* pClassName, void* state, delegate* unmanaged<byte*, void*, void> callback)
    {
        using var text = new UnmanagedMemoryStream(pText, textLength);
        var className  = Marshal.PtrToStringUTF8((nint)pClassName)!;

        try
        {
            // Parse the source into a SyntaxTree and use NamespaceSyntaxWalker
            // to determine which namespace the requested class is located in.
            var tree   = SyntaxFactory.ParseSyntaxTree(SourceText.From(text));
            var walker = new NamespaceSyntaxWalker(className);
            walker.Visit(tree.GetRoot());

            // Now we either have a namespace or an empty string.
            var namespaceName = Marshal.StringToCoTaskMemUTF8(walker.Namespace);

            try
            {
                callback((byte*)namespaceName, state);
            }
            finally
            {
                Marshal.FreeCoTaskMem(namespaceName);
            }
        }
        catch (Exception ex)
        {
            return Marshal.GetHRForException(ex);
        }

        return 0;
    }
}
